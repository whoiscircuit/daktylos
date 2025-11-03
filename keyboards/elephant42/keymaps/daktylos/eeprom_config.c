#include QMK_KEYBOARD_H
#include "eeprom_config.h"
#include "transactions.h"

user_config_t eeprom;

void setup_config(void) {
    g_tapping_term = eeprom.tap_term;
    // send the user config to the slave side so that the eeprom is synced on both sides
    if (is_keyboard_master()) transaction_rpc_send(USER_CONFIG_SYNC, sizeof(eeprom.raw), &eeprom.raw);
}


void user_config_sync_slave_handler(uint8_t in_buflen, const void *sync_data, uint8_t out_buflen, void *out_data) {
    eeprom.raw = *(uint32_t *)sync_data;
    eeconfig_update_user(eeprom.raw);
    setup_config();
}

void eeconfig_init_user() {
    eeprom.tap_term = TAPPING_TERM;
}