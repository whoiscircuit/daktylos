#pragma once
#include <signal.h>
#include "hidapi.h"
#define MAX(a,b) ((a) > (b) ? (a) : (b))

void  sleep_for_ms(unsigned int ms);
int   check_signal(sigset_t *set);
void  find_device_path(unsigned short vendor_id, unsigned short product_id, unsigned short usage_page, unsigned short usage_id,char* result);
hid_device *open_device(char* path);
hid_device *wait_for_device(unsigned short vendor_id, unsigned short product_id, unsigned short usage_page, unsigned short usage_id);
