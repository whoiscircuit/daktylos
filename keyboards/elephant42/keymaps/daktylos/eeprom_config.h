#include QMK_KEYBOARD_H
typedef union {
    uint32_t raw;
    struct {
        uint8_t tap_term;
    };
} user_config_t;

extern user_config_t user_config;

void user_config_sync_slave_handler(uint8_t in_buflen, const void *sync_data, uint8_t out_buflen, void *out_data);
void setup_config(void);