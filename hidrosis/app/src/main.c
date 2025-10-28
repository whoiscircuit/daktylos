#include <stdint.h>
#include <hidapi.h>
#include <string.h>
#include <wchar.h>
#include "signal_control.h"
#include "layout.h"
#include "os_type.h"
#include "util.h"
#include "log.h"

#define KEYBOARD_VID 0x4649
#define KEYBOARD_PID 0x0721
#define MAX_STR 255

#define RAW_USAGE_PAGE 0xFF69
#define RAW_USAGE_ID 0x69
#define REPORT_SIZE 32

typedef union {
    unsigned char buf[REPORT_SIZE + 1];
    struct {
        uint8_t   report_id; // should always be 0x00
        uint8_t os_type;
        uint8_t  active_layout;
    };
} HIDReport;

int main() {
    log_init("hidrosis");
    log_set_level(LOG_LEVEL_TRACE);
    LOG_INFO("starting hidrosis service...");

    int         res;
    int sig;
    hid_device *device = NULL;
    wchar_t     wstr[MAX_STR];
    HIDReport   report;
    memset(report.buf, 0, REPORT_SIZE + 1);

    LOG_TRACE("setting up signal handlers...");
    signal_init();

    LOG_DEBUG("initializing hidapi library...");
    res = hid_init();
    if (res == -1) {
        LOG_FATAL("Failed to initialize hidapi library! quitting.\n");
        const wchar_t *err = hid_error(NULL);
        LOG_ERROR("Error: %ls", err);
        return 1;
    }

    // wait for the keyboard to be connected
    LOG_INFO("waiting for keyboard to be connected...");
    device = wait_for_device(KEYBOARD_VID, KEYBOARD_PID, RAW_USAGE_PAGE, RAW_USAGE_ID);
    if(device == NULL){
        return 1;
    }

    // Read the Manufacturer String
    hid_get_manufacturer_string(device, wstr, MAX_STR);
    LOG_DEBUG("Manufacturer String: %ls", wstr);

    // Read the Product String
    hid_get_product_string(device, wstr, MAX_STR);
    LOG_DEBUG("Product String: %ls", wstr);

    report.os_type = get_os_type();
    if (report.os_type == OS_TYPE_UNKNOWN) {
        LOG_WARN("Failed to detect the OS type!");
    }
    else {
        LOG_DEBUG("Detected OS type: %s", os_type_to_string(report.os_type));
    }

    res = init_keyboard_layout();
    if(res != 0){
        LOG_FATAL("a fatal problem occured during initlaization of keyboard layout setup.");
        return -1;
    }

    LOG_INFO("Starting main loop...");
    bool should_update = true;
    int wait_time = 200;
    for(;;){
        keyboard_layout_t layout = get_keyboard_layout();
        if (layout == LAYOUT_UNKNOWN) {
            LOG_WARN("Failed to get the active keyboard layout!");
            wait_time = MIN((int)(wait_time * 1.2),30000);
        } else {
            wait_time = 200; // reset wait time
            if (layout != report.active_layout) {
                report.active_layout = layout;
                should_update = true;
                LOG_INFO("Active keyboard layout changed to: %s", layout_to_string(layout));
            }
        }
        if(should_update){
            LOG_DEBUG("Sending HID Report: os_type=%s, active_layout=%s",
                      os_type_to_string(report.os_type),
                      layout_to_string(report.active_layout));
            res = hid_write(device, report.buf, REPORT_SIZE);
            if (res == -1) {
                const wchar_t *err = hid_error(device);
                LOG_ERROR("Failed to send HID Report to the keyboard.");
                LOG_ERROR("Error: %ls", err);
                wait_time = MIN((int)(wait_time * 1.2),30000);
                // check if the device is still connected
                char path[256] = {0};
                find_device_path(KEYBOARD_VID, KEYBOARD_PID, RAW_USAGE_PAGE, RAW_USAGE_ID,path);
                if (path[0] == '\0') {
                    LOG_WARN("keyboard disconnected, waiting for it to be reconnected...");
                    hid_close(device);
                    device = wait_for_device(KEYBOARD_VID, KEYBOARD_PID, RAW_USAGE_PAGE, RAW_USAGE_ID);
                    if(device == NULL){
                        break;
                    }
                    LOG_INFO("keyboard reconnected. continuing...");
                }
            }
            else {
                wait_time = 200;
                LOG_DEBUG("HID Report sent successfully.");
                should_update = false;
            }
        }
        sig = check_signal();
        if (sig){
            LOG_WARN("termination signal received, quitting...");
            break;
        }
        sleep_for_ms(wait_time);
    }

    hid_close(device);
    res = hid_exit();
    close_keyboard_layout();
    if (res == -1) {
        LOG_ERROR("Failed to exit hidapi library safely. quitting anyways.");
        return 1;
    }

    return 0;
}
