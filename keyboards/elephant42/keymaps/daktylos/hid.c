#include QMK_KEYBOARD_H
#include "hid.h"

hid_state_t hid_state = {0x00};

// receive hid report from hidrosis from the host 
void raw_hid_receive(uint8_t *data, uint8_t length) {
    hid_state.raw = *data;
}