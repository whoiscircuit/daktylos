#pragma once
#include QMK_KEYBOARD_H

enum layer_names {
    _COLEMAKDH,
    _FARSI,
    _COLEMAKDH_INTL, // for when the Us (International) layout is being used on the host
    ACCENT, // for typing accent letters and international symbols
    _COLEMAKDH_OVERLAY, // for when the keyboard is farsi and a mod key is pressed down
    NUM,
    FUN,
    SYM,
    NAV,
    MOS,
    MED,
    BLOCK_LEFT, // for when a mod key from the left hand is pressed
    BLOCK_RIGHT, // for when a mod key from the right hand is pressed
    BLOCK_RIGHT_INTL,
    _JOYSTICK, // joystick mode
    _MENU,
    NUMBER_OF_LAYERS,
};

#define LT_NUM_ENT LT(NUM, KC_ENT)
#define LT_SYM_BSPC LT(SYM, KC_BSPC)
#define LT_FUN_DEL LT(FUN, KC_DEL)
#define LT_NAV_SPC LT(NAV, KC_SPC)
#define LT_MOS_TAB LT(MOS, KC_TAB)
#define LT_MED_ESC LT(MED, KC_ESC)

#define MT_LGUI_A MT(MOD_LGUI, KC_A)
#define MT_LALT_R MT(MOD_LALT, KC_R)
#define MT_LCTL_S MT(MOD_LCTL, KC_S)
#define MT_LSFT_T MT(MOD_LSFT, KC_T)

#define MT_RSFT_N MT(MOD_RSFT, KC_N)
#define MT_RCTL_E MT(MOD_RCTL, KC_E)
#define MT_RALT_I MT(MOD_RALT, KC_I)
#define MT_RGUI_O MT(MOD_RGUI, KC_O)

// for farsi
#define MT_LALT_S MT(MOD_LALT, KC_S)
#define MT_LCTL_D MT(MOD_LCTL, KC_D)
#define MT_LSFT_F MT(MOD_LSFT, KC_F)

#define MT_RSFT_J MT(MOD_RSFT, KC_J)
#define MT_RCTL_K MT(MOD_RCTL, KC_K)
#define MT_RALT_L MT(MOD_RALT, KC_L)
#define MT_RGUI_SCLN MT(MOD_RGUI, KC_SCLN)

// for colemakdh international
#define LT_ACCENT_G LT(ACCENT, KC_G)
#define LT_ACCENT_M LT(ACCENT, KC_M)
#define MT_LALT_I MT(MOD_LALT, KC_I)
#define LM_NUM LM(NUM,MOD_RALT)
#define LM_SYM LM(SYM,MOD_RALT)

// accented characters
#define KC_A_UMLAUT RALT(KC_Q)
#define KC_O_UMLAUT RALT(KC_P)
#define KC_U_UMLAUT RALT(KC_Y)
#define KC_SS RALT(KC_S)
#define KC_COPYRIGHT RALT(KC_R)

enum custom_keycodes {
    MY_MENU = SAFE_RANGE,
    MY_UP,
    MY_DOWN,
    MY_LEFT,
    MY_RIGHT,
    MY_SELECT,
};
