#include QMK_KEYBOARD_H
#include "oled.h"
#include "hid.h"
#include "eeprom_config.h"

oled_state_t oled_state = {0x00};


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270; // flips the display 180 degrees if offhand
}

bool oled_task_user(void) {
    oled_clear();
    switch (oled_state.mode) {
        case OLED_OFF:
            break;
        case OLED_MENU:
            if (!is_keyboard_master()) {
                switch (hid_state.os_type) {
                    case OS_WINDOWS:
                        oled_write_P(PSTR("\x53\x54\x5F\x1A\x1E"), false);
                        oled_write_P(PSTR("\x55\x56\x22\x14\x19"), false);
                        break;
                    case OS_MACOS:
                        oled_write_P(PSTR("\x4F\x50\x5F\x1A\x1E"), false);
                        oled_write_P(PSTR("\x51\x52\x18\x0C\x0E"), false);
                        break;
                    case OS_LINUX:
                        oled_write_P(PSTR("\x57\x58\x5F\x1A\x1E"), false);
                        oled_write_P(PSTR("\x59\x5A\x17\x14\x19"), false);
                        break;
                    default:
                        oled_write_P(PSTR("\x5B\x5C\x5F\x1A\x1E"), false);
                        oled_write_P(PSTR("\x5D\x5E\x0B\x0B\x0B"), false);
                        break;
                }
                oled_advance_page(false);
                switch (hid_state.active_layout) {
                    case LAYOUT_ENGLISH:
                        oled_write_P(PSTR("\x5F\x10\x19\x12\x5F"), false);
                        break;
                    case LAYOUT_FARSI:
                    case LAYOUT_FARSI_NON_STANDARD:
                        oled_write_P(PSTR("\x5F\x11\x0C\x1D\x5F"), false);
                        break;
                    case LAYOUT_INTERNATIONAL:
                    case LAYOUT_INTERNATIONAL_WITHOUT_DEAD_KEYS:
                        oled_write_P(PSTR("\x5F\x14\x19\x1F\x5F"), false);
                        break;
                    default:
                        break;
                }
            } else {
                oled_write_P(PSTR("\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F"), oled_state.menu_item == MENU_JOYSTICK);
                oled_write_P(PSTR("\x5F\x15\x1A\x24\x5F"), oled_state.menu_item == MENU_JOYSTICK);
                oled_write_P(PSTR("\x1E\x1F\x14\x0E\x16"), oled_state.menu_item == MENU_JOYSTICK);
                oled_write_P(PSTR("\x5F\x26\x27\x28\x5F\x29\x2A\x2B\x2C\x2D\x5F\x2E\x2F\x30\x5F"), oled_state.menu_item == MENU_PREFS);
                oled_write_P(PSTR("\x1B\x1D\x10\x11\x1E"), oled_state.menu_item == MENU_PREFS);
                oled_advance_page(false);
                oled_write_P(PSTR("\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E"), oled_state.menu_item == MENU_FLASH);
                oled_write_P(PSTR("\x11\x17\x0C\x1E\x13"), oled_state.menu_item == MENU_FLASH);
                oled_advance_page(false);
            }
            break;
        case OLED_BOOTLOADER:
            oled_set_cursor(0, 4);
            oled_write_P(PSTR("\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E"), false);
            oled_advance_page(false);
            oled_write_P(PSTR("\x11\x17\x0C\x1E\x13"), false);
            break;
        case OLED_JOYSTICK:
            oled_set_cursor(0, 4);
            oled_write_P(PSTR("\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F"), false);
            oled_write_P(PSTR("\x5F\x15\x1A\x24\x5F"), false);
            oled_write_P(PSTR("\x1E\x1F\x14\x0E\x16"), false);
            break;
        case OLED_PREFS:
            if (is_keyboard_master()) {
                oled_write_P(PSTR("\x5F\x1F\x0C\x1B\x5F"), oled_state.prefs_index == PREF_TAP_TERM);
                oled_write_P(PSTR("\x1F\x10\x1D\x18\x5F"), oled_state.prefs_index == PREF_TAP_TERM);
                oled_state.prefs_index == PREF_TAP_TERM ? oled_write_P(PSTR("\x2C"), false) : oled_advance_char();
                eeprom.tap_term >= 100 ? oled_write_char((eeprom.tap_term / 100), false) : oled_write_char(0, false);
                eeprom.tap_term >= 10 ? oled_write_char((eeprom.tap_term / 10) % 10, false) : oled_write_char(0, false);
                oled_write_char(eeprom.tap_term % 10, false);
                oled_state.prefs_index == PREF_TAP_TERM ? oled_write_P(PSTR("\x2A"), false) : oled_advance_char();
            }
            break;
        default:
            break;
    }
    return false;
}