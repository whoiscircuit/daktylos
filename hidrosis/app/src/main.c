#include <stdint.h>
#include <stdio.h>
#include <hidapi.h>
#include <wchar.h>

#define KEYBOARD_VID 0x4649
#define KEYBOARD_PID 0x0721
#define MAX_STR 255

#define RAW_USAGE_PAGE 0xFF60
#define RAW_USAGE_ID 0x69


typedef union {
    uint32_t raw;
    struct {
        uint8_t first_byte;
    };
} HIDReport;


int main() {
    int res;
    hid_device *device;
    wchar_t wstr[MAX_STR];
    unsigned char buf[5] = {0,0,0,0,0};
    HIDReport report;
    report.raw = buf[1];
    report.first_byte = 1;

    res = hid_init();
    if(res == -1){
        printf("Failed to initialize hidapi library! quitting.\n");
        return 1;
    }

    device = hid_open(KEYBOARD_VID,KEYBOARD_PID,NULL);
    // TODO: enumerate devices and filter based on USAGE_PAGE and USAGE_ID

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

    res = hid_write(device,(const unsigned char*)&report,5);
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
