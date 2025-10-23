#include "util.h"
#include <stdio.h>
#include "hidapi.h"
#include "log.h"
#include <signal.h>
#include "signal_control.h"
#ifdef _WIN32
#    include <windows.h>
#else
#    include <unistd.h>
#endif

void sleep_for_ms(unsigned int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

void find_device_path(unsigned short vendor_id, unsigned short product_id, unsigned short usage_page, unsigned short usage_id, char *result) {
    struct hid_device_info *cur_device   = hid_enumerate(vendor_id, product_id);
    struct hid_device_info *first_device = cur_device;
    while (cur_device != NULL) {
        LOG_TRACE("checking device: path=%s, vid=0x%04hx, pid=0x%04hx, serial_number=%ls, release_number=0x%hx, manufacturer_string=%ls, product_string=%ls, usage_page=0x%hx, usage=0x%hx", cur_device->path, cur_device->vendor_id, cur_device->product_id, cur_device->serial_number, cur_device->release_number, cur_device->manufacturer_string, cur_device->product_string, cur_device->usage_page, cur_device->usage);

        if (cur_device->usage_page == usage_page && cur_device->usage == usage_id) {
            LOG_INFO("keyboard found, path=%s", cur_device->path);
            snprintf(result, 256, "%s", cur_device->path);
            break;
        }
        cur_device = cur_device->next;
    }
    hid_free_enumeration(first_device);
}

hid_device *open_device(char *path) {
    hid_device *device = hid_open_path(path);
    if (device == NULL) {
        LOG_ERROR("failed to open the device at path %s", path);
        const wchar_t *err = hid_error(NULL);
        LOG_ERROR("Error: %ls", err);
    } else {
        LOG_INFO("connected to the keyboard successfully.");
    }
    return device;
}

hid_device *wait_for_device(unsigned short vendor_id, unsigned short product_id, unsigned short usage_page, unsigned short usage_id) {
    hid_device *device = NULL;
    char        path[256] = {0};
    int wait_time = 1000;
    while (device == NULL) {
        find_device_path(vendor_id, product_id, usage_page, usage_id, path);
        if (path[0] != '\0') {
            wait_time = 1000;
            device = open_device(path);
        }
        if (device == NULL) {
            wait_time = MAX((int)(wait_time * 1.2),3000);
            sleep_for_ms(wait_time);
        }
        sig = check_signal(&set);
        if (sig == SIGINT || sig == SIGTERM){
            LOG_WARN("termination signal received, quitting...");
            break;
        }
    }
    return device;
}
