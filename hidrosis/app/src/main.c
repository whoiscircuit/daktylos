#include <stdint.h>
#include <stdio.h>
#include <hidapi.h>
#include <string.h>
#include <wchar.h>

#define KEYBOARD_VID 0x4649
#define KEYBOARD_PID 0x0721
#define MAX_STR 255

#define RAW_USAGE_PAGE 0xFF69
#define RAW_USAGE_ID 0x69
#define REPORT_SIZE 32


typedef union {
    unsigned char buf[REPORT_SIZE + 1];
    struct {
        uint8_t report_id; // should always be 0x00
        uint8_t os_type :2;
    };
} HIDReport;

uint8_t get_os_type(){
#ifdef _WIN32
    return 0x01;
#elif __APPLE__
    return 0x02;
#elif __linux__
    return 0x03;
#else
    return 0x00;
#endif
}

int main() {
    int res;
    hid_device *device;
    wchar_t wstr[MAX_STR];
    HIDReport report;
    memset(report.buf,0,REPORT_SIZE + 1);

    res = hid_init();
    if(res == -1){
        printf("Failed to initialize hidapi library! quitting.\n");
        return 1;
    }

    struct hid_device_info* cur_device = hid_enumerate(KEYBOARD_VID,KEYBOARD_PID);
    while(cur_device != NULL){
        if(cur_device->usage_page == RAW_USAGE_PAGE && cur_device->usage == RAW_USAGE_ID){
            device = hid_open_path(cur_device->path);
            break;
        }
        cur_device = cur_device->next;
    }

    if(!device){
        printf("Unable to open device! quitting.\n");
        // TODO: create a loop to constantly check for the device to come online
        hid_exit();
        return 1;
    }

    printf("Connected to the keyboard successfully.\n");
	// Read the Manufacturer String
	res = hid_get_manufacturer_string(device, wstr, MAX_STR);
	printf("Manufacturer String: %ls\n", wstr);

	// Read the Product String
	res = hid_get_product_string(device, wstr, MAX_STR);
	printf("Product String: %ls\n", wstr);


    // TODO: keep seding the hid_report in an interval untill forever
    report.os_type = get_os_type();
    res = hid_write(device,report.buf,REPORT_SIZE);
    if(res == -1){
        printf("Failed to send HID Report to the keyboard. quitting\n");
        return -1;
    }

    hid_close(device);
    res = hid_exit();
    if(res == -1){
        printf("Failed to exit hidapi library safely. quitting anyways.\n");
        return 1;
    }

    return 0;
}
