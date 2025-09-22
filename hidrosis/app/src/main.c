#include <stdint.h>
#include <stdio.h>
#include <hidapi.h>
#include <wchar.h>

#define KEYBOARD_VID 0x4649
#define KEYBOARD_PID 0x0721
#define MAX_STR 255


typedef union {
    uint32_t raw;
    struct {
        uint8_t report_type; // must always be 0x00
        uint8_t os_type :2;
        uint8_t keyboard_layout :3;
    };
} HIDReport;


int main() {
    int res;
    hid_device *device;
    wchar_t wstr[MAX_STR];

    res = hid_init();
    if(res == -1){
        printf("Failed to initialize hidapi library! quitting.\n");
        return 1;
    }

    device = hid_open(KEYBOARD_VID,KEYBOARD_PID,NULL);

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

	// Read the Serial Number String
	res = hid_get_serial_number_string(device, wstr, MAX_STR);
	printf("Serial Number String: (%d) %ls\n", wstr[0], wstr);

	// Read Indexed String 1
	res = hid_get_indexed_string(device, 1, wstr, MAX_STR);
	printf("Indexed String 1: %ls\n", wstr);

    HIDReport report = {
        .report_type = 0x00,
        .os_type = 0x01,
        .keyboard_layout = 0x01
    };

    res = hid_write(device,(const unsigned char*)&report,4);
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
