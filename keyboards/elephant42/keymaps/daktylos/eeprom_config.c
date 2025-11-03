#include QMK_KEYBOARD_H
#include "eeprom_config.h"
#include "transactions.h"

user_config_t user_config;

void setup_config(void) {
    g_tapping_term = user_config.tap_term;
    // send the user config to the slave side so that the eeprom is synced on both sides
    if (is_keyboard_master()) transaction_rpc_send(USER_CONFIG_SYNC, sizeof(user_config.raw), &user_config.raw);
}


void user_config_sync_slave_handler(uint8_t in_buflen, const void *sync_data, uint8_t out_buflen, void *out_data) {
    user_config.raw = *(uint32_t *)sync_data;
    eeconfig_update_user(user_config.raw);
    setup_config();
}

void eeconfig_init_user() {
    user_config.tap_term = TAPPING_TERM;
}