#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <hidapi.h>
#include <string.h>
#include <wchar.h>
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
        os_type_t os_type : 2;
        unsigned  active_layout : 2;
    };
} HIDReport;

int main() {
    log_init("hidrosis");
    LOG_INFO("starting hidrosis service...");

    sigset_t set;
    int sig;
    int         res;
    hid_device *device = NULL;
    wchar_t     wstr[MAX_STR];
    HIDReport   report;
    memset(report.buf, 0, REPORT_SIZE + 1);


    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTERM);
    sigprocmask(SIG_BLOCK, &set, NULL);

    res = hid_init();
    if (res == -1) {
        LOG_FATAL("Failed to initialize hidapi library! quitting.\n");
        return 1;
    }

    // wait for the keyboard to be connected
    LOG_INFO("waiting for keyboard to be connected...");
    while(device == NULL) {
        struct hid_device_info *cur_device = hid_enumerate(KEYBOARD_VID, KEYBOARD_PID);
        struct hid_device_info *first_device = cur_device;
        while (cur_device != NULL) {
            if (cur_device->usage_page == RAW_USAGE_PAGE && cur_device->usage == RAW_USAGE_ID) {
                LOG_INFO("keyboard found, connecting...");
                device = hid_open_path(cur_device->path);
                if(device == NULL) {
                    LOG_ERROR("failed to open the device at path %s", cur_device->path);
                }
                else {
                    LOG_INFO("connected to the keyboard successfully.");
                    break;
                }
            }
            cur_device = cur_device->next;
        }
        hid_free_enumeration(first_device);
        sleep_for_seconds(1);
    }

    // Read the Manufacturer String
    res = hid_get_manufacturer_string(device, wstr, MAX_STR);
    LOG_DEBUG("Manufacturer String: %ls", wstr);

    // Read the Product String
    res = hid_get_product_string(device, wstr, MAX_STR);
    LOG_DEBUG("Product String: %ls", wstr);

    report.os_type = get_os_type();
    if (report.os_type == OS_TYPE_UNKNOWN) {
        LOG_WARN("Failed to detect the OS type!");
    }
    else {
        LOG_DEBUG("Detected OS type: %s", os_type_to_string(report.os_type));
    }

    bool should_update = false;
    for (;;) {
        keyboard_layout_t layout = get_keyboard_layout();
        if (layout == LAYOUT_UNKNOWN) {
            LOG_WARN("Failed to get the active keyboard layout!");
        } else {
            if (layout != report.active_layout) {
                report.active_layout = layout;
                should_update = true;
                LOG_INFO("Active keyboard layout changed to: %s", layout_to_string(layout));
            }
        }
        if(should_update){
            res = hid_write(device, report.buf, REPORT_SIZE);
            if (res == -1) {
                LOG_ERROR("Failed to send HID Report to the keyboard.");
            }
            else {
                should_update = false;
            }
        }
        sigwait(&set, &sig);
        if (sig == SIGINT || sig == SIGTERM){
            LOG_INFO("termination signal received, quitting...");
            break;
        }
        sleep_for_seconds(1);
    }

    hid_close(device);
    res = hid_exit();
    if (res == -1) {
        LOG_ERROR("Failed to exit hidapi library safely. quitting anyways.");
        return 1;
    }

    return 0;
}
