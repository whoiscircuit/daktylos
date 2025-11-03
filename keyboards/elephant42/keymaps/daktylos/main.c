#include QMK_KEYBOARD_H
#include "keymap.h"
#include "raw_hid.h"
#include "key_overrides.h"
#include "hid.h"
#include "oled.h"
#include "eeprom_config.h"
#include "transactions.h"

#define GET_MOD_FROM_TAP_HOLD(tap_hold_keycode) (((tap_hold_keycode) & 0x0F00) >> 8)
#define GET_LAYER_FROM_TAP_HOLD(tap_hold_keycode) (((tap_hold_keycode) & 0x0F00) >> 8)
#define GET_KEYCODE_FROM_TAP_HOLD(tap_hold_keycode) ((tap_hold_keycode) & 0xFF)

int MOD_MASK_RIGHT = (0xF0);
int MOD_MASK_LEFT  = (0x0F);

void state_sync_slave_handler(uint8_t in_buflen, const void *sync_data, uint8_t out_buflen, void *out_data) {
    oled_state = *(oled_state_t *)sync_data;
    hid_state  = *(hid_state_t *)(sync_data + 1);
}

void keyboard_post_init_user() {
    user_config.raw = eeconfig_read_user();
    setup_config();
    // for sending presistent setting to the other side
    transaction_register_rpc(USER_CONFIG_SYNC, user_config_sync_slave_handler);
    // for sending the non-presistent current state of oled, hid, etc..
    transaction_register_rpc(STATE_SYNC, state_sync_slave_handler);
}

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    // when a mod from the one side is pressed block the keys on that side to prevent accidental keypresses.
    // when a mod from the one side is released unblock the keys on that side.
    int layer = hid_state.active_layout == LAYOUT_INTERNATIONAL ? BLOCK_RIGHT_INTL : BLOCK_RIGHT;
    int mods  = get_mods();
    if (mods & MOD_MASK_RIGHT) {
        layer_on(layer);
    } else {
        layer_off(layer);
    }

    if (mods & MOD_MASK_LEFT) {
        layer_on(BLOCK_LEFT);
    } else {
        layer_off(BLOCK_LEFT);
    }
    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    // if the farsi layout is active and any mod key other than shift is pressed temporarily switch to the colemak-dh overlay
    // this is done to make keyboard shotcuts such as Ctrl+s persistent on both layouts
    if (get_mods() & ~MOD_MASK_SHIFT) {
        if (default_layer_state & (1 << _FARSI)) {
            layer_on(_COLEMAKDH_OVERLAY);
        }
    } else {
        layer_off(_COLEMAKDH_OVERLAY);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT_NUM_ENT:
        case LT_SYM_BSPC:
        case LT_FUN_DEL:
            // when a mod key from the right side is pressed the thumb keys should only act as temporarily layer switchers
            // this is done to prevent accidental thumb key registers
            if (get_mods() & MOD_MASK_RIGHT) {
                if (record->event.pressed) {
                    layer_on(GET_LAYER_FROM_TAP_HOLD(keycode));
                } else {
                    layer_off(GET_LAYER_FROM_TAP_HOLD(keycode));
                }
                return false;
            }
            break;
        case LT_NAV_SPC:
            // if hidrosis integration is not active we have to manually toggle between english and farsi layout when Win+Space is pressed
            // this is so that the keyboard maintains functionality even if hidrosis is not installed on the host machine
            if (!record->event.pressed && hid_state.os_type == OS_UNKNOWN && get_mods() & MOD_BIT(KC_RGUI)) {
                if (hid_state.active_layout == LAYOUT_ENGLISH) {
                    hid_state.active_layout = LAYOUT_FARSI;
                } else {
                    hid_state.active_layout = LAYOUT_ENGLISH;
                }
            }
        case LT_MOS_TAB:
        case LT_MED_ESC:
            // when a mod key from the left side is pressed the thumb keys should only act as temporarily layer switchers
            // this is done to prevent accidental thumb key registers
            if (get_mods() & MOD_MASK_LEFT) {
                if (record->event.pressed) {
                    layer_on(GET_LAYER_FROM_TAP_HOLD(keycode));
                } else {
                    layer_off(GET_LAYER_FROM_TAP_HOLD(keycode));
                }
                return false;
            }
            break;
        case MT_LSFT_T:
        case MT_LSFT_F:
            // this is done to keep BOTH_SHIFTS_TURNS_ON_CAPS_WORD working. otherwise it would fail because of the code below
            if (get_mods() & MOD_BIT(KC_RSFT)) break;
        case MT_LCTL_S:
        case MT_LALT_R:
        case MT_LGUI_A:
        case MT_LCTL_D:
        case MT_LALT_S:
            // when a mod key from the right side is pressed the mod functionality of the home row mods on the left side should be disabled
            // so that they act as normal keys no matter if they are tapped or held. this is done to prevent accidental keypresses.
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_RIGHT) {
                    register_code(GET_KEYCODE_FROM_TAP_HOLD(keycode));
                    return false;
                }
            } else {
                unregister_code(GET_KEYCODE_FROM_TAP_HOLD(keycode));
                return true;
            }
            break;

        case MT_RSFT_N:
        case MT_RSFT_J:
            // this is done to keep BOTH_SHIFTS_TURNS_ON_CAPS_WORD working. otherwise it would fail because of the code below
            if (get_mods() & MOD_BIT(KC_LSFT)) break;
        case MT_RCTL_E:
        case MT_RALT_I:
        case MT_RGUI_O:
        case MT_RCTL_K:
        case MT_RALT_L:
        case MT_LALT_I:
        case MT_RGUI_SCLN:
            // when a mod key from the left side is pressed the mod functionality of the home row mods on the right side should be disabled
            // so that they act as normal keys no matter if they are tapped or held. this is done to prevent accidental keypresses.
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_LEFT) {
                    register_code(GET_KEYCODE_FROM_TAP_HOLD(keycode));
                    return false;
                }
            } else {
                unregister_code(GET_KEYCODE_FROM_TAP_HOLD(keycode));
                return true;
            }
            break;
        case MY_MENU:
            // the menu button is a custom button that will toggle the menu GUI in the OLED display.
            // by enabling the oled state for menu and switching the active layout to _MENU
            if (!record->event.pressed) {
                if (oled_state.mode == OLED_MENU) {
                    switch (hid_state.active_layout) {
                        case LAYOUT_ENGLISH:
                            set_single_default_layer(_COLEMAKDH);
                            break;
                        case LAYOUT_FARSI:
                        case LAYOUT_FARSI_NON_STANDARD:
                            set_single_default_layer(_FARSI);
                            break;
                        case LAYOUT_INTERNATIONAL:
                        case LAYOUT_INTERNATIONAL_WITHOUT_DEAD_KEYS:
                            set_single_default_layer(_COLEMAKDH_INTL);
                            break;
                    }
                    oled_state.mode = OLED_OFF;
                } else {
                    set_single_default_layer(_MENU);
                    oled_state.prefs_index = 0;
                    oled_state.mode        = OLED_MENU;
                }
            }
            break;
        case MY_DOWN:
            // navigate down in menu display of the keyboard
            if (!record->event.pressed) {
                if (oled_state.mode == OLED_MENU) {
                    oled_state.menu_item = (oled_state.menu_item + 1) % NUMBER_OF_MENU_ITEMS;
                } else if (oled_state.mode == OLED_PREFS) {
                    oled_state.prefs_index = (oled_state.prefs_index + 1) % NUMBER_OF_PREFS_ITEMS;
                }
            }
            break;
        case MY_UP:
            // navigate up in menu display of the keyboard
            if (!record->event.pressed) {
                if (oled_state.mode == OLED_MENU) {
                    if (oled_state.menu_item == 0)
                        oled_state.menu_item = NUMBER_OF_MENU_ITEMS - 1;
                    else
                        oled_state.menu_item = (oled_state.menu_item - 1) % NUMBER_OF_MENU_ITEMS;
                } else if (oled_state.mode == OLED_PREFS) {
                    if (oled_state.prefs_index == 0)
                        oled_state.prefs_index = NUMBER_OF_PREFS_ITEMS - 1;
                    else
                        oled_state.prefs_index = (oled_state.prefs_index - 1) % NUMBER_OF_PREFS_ITEMS;
                }
            }
            break;
        case MY_LEFT:
            // navigate left in menu display of the keyboard
            if (record->event.pressed || oled_state.mode != OLED_PREFS) return false;
            if (oled_state.prefs_index == PREF_TAP_TERM) {
                user_config.tap_term = (user_config.tap_term / 5 * 5) - 5;
            }

            eeconfig_update_user(user_config.raw);
            setup_config();
            break;
        case MY_RIGHT:
            // navigate right in menu display of the keyboard
            if (record->event.pressed || oled_state.mode != OLED_PREFS) return false;
            user_config.tap_term = (user_config.tap_term / 5 * 5) + 5;
            eeconfig_update_user(user_config.raw);
            setup_config();
            break;
        case MY_SELECT:
            // select an item in the menu display of the keyboard
            if (!record->event.pressed) {
                switch (oled_state.menu_item) {
                    case MENU_JOYSTICK:
                        set_single_default_layer(_JOYSTICK);
                        oled_state.mode = OLED_JOYSTICK;
                        break;
                    case MENU_PREFS:
                        set_single_default_layer(_MENU);
                        oled_state.mode        = OLED_PREFS;
                        oled_state.prefs_index = 0;
                        break;
                    case MENU_FLASH:
                        reset_keyboard();
                        break;
                    default:
                        break;
                }
            }
            break;
        case KC_GRV:
        case KC_DQUO:
        case KC_QUOT:
        case KC_TILD:
            // disable dead keys (not ideal. the implementation of dead keys in windows is not good!)
            if (hid_state.active_layout == LAYOUT_INTERNATIONAL && !record->event.pressed) {
                wait_ms(40);
                tap_code(KC_SPC);
                break;
            }
            return true;
    }
    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT_LGUI_A:
        case MT_RGUI_O:
        case MT_RGUI_SCLN:
            return g_tapping_term * 1.5;
        case MT_RCTL_E:
        case MT_LCTL_S:
        case MT_RCTL_K:
        case MT_LCTL_D:
            return g_tapping_term * 0.8;
        case MT_RSFT_N:
        case MT_LSFT_T:
        case MT_RSFT_J:
        case MT_LSFT_F:
            return g_tapping_term * 0.7;
        default:
            return g_tapping_term;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT_RCTL_E:
        case MT_LCTL_S:
        case MT_RSFT_N:
        case MT_LSFT_T:
        case MT_RCTL_K:
        case MT_LCTL_D:
        case MT_RSFT_J:
        case MT_LSFT_F:
            return 0;
        case LT_NAV_SPC:
        case LT_SYM_BSPC:
            return g_tapping_term * 0.5;
        default:
            return g_tapping_term;
    }
}

void matrix_scan_user(void) {
    static uint16_t my_boot_timer      = 0;
    static uint16_t my_boot_hold_timer = 0;
    static bool     jump_to_bootloader = false;

    if (jump_to_bootloader && timer_elapsed(my_boot_timer) > 200) {
        reset_keyboard();
    }
    // logic for restart and jumping to bootloader based on pressing the two thumb keys
    if ((matrix_is_on(7, 5) && matrix_is_on(7, 3)) || (matrix_is_on(3, 3) && matrix_is_on(3, 5))) {
        if (my_boot_hold_timer == 0) {
            my_boot_hold_timer = timer_read();
        }
    } else if (my_boot_hold_timer != 0) {
        if (timer_elapsed(my_boot_hold_timer) > g_tapping_term * 2) {
            oled_state.mode    = OLED_BOOTLOADER;
            jump_to_bootloader = true;
            my_boot_timer      = timer_read();
        } else if (timer_elapsed(my_boot_hold_timer) > g_tapping_term / 2) {
            soft_reset_keyboard();
        }
        my_boot_hold_timer = 0;
    }
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        // Interact with slave every 500ms
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > 200) {
            uint16_t raw = oled_state.raw << 8 & hid_state.raw;
            transaction_rpc_send(STATE_SYNC, sizeof(uint16_t), &raw);
            last_sync = timer_read32();
        }
        if (oled_state.mode == OLED_OFF) {
            switch (hid_state.active_layout) {
                case LAYOUT_ENGLISH:
                    set_single_default_layer(_COLEMAKDH);
                    MOD_MASK_RIGHT = (0xF0);
                    MOD_MASK_LEFT  = (0x0F);
                    break;
                case LAYOUT_FARSI_NON_STANDARD:
                    is_persian_p_override_enabled = true;
                    MOD_MASK_RIGHT                = (0xF0);
                    MOD_MASK_LEFT                 = (0x0F);
                    set_single_default_layer(_FARSI);
                    break;
                case LAYOUT_FARSI:
                    is_persian_p_override_enabled = false;
                    MOD_MASK_RIGHT                = (0xF0);
                    MOD_MASK_LEFT                 = (0x0F);
                    set_single_default_layer(_FARSI);
                    break;
                case LAYOUT_INTERNATIONAL:
                case LAYOUT_INTERNATIONAL_WITHOUT_DEAD_KEYS:
                    set_single_default_layer(_COLEMAKDH_INTL);
                    MOD_MASK_RIGHT = MOD_RSFT & MOD_RCTL & MOD_RGUI;
                    MOD_MASK_LEFT  = MOD_LSFT & MOD_LCTL & MOD_LGUI;
                    break;
                default:
                    break;
            }
        }
    }
}

// QMK optimizations
#ifndef MAGIC_ENABLE
uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}
#endif

#ifndef MAGIC_ENABLE
uint8_t mod_config(uint8_t mod) {
    return mod;
}
#endif