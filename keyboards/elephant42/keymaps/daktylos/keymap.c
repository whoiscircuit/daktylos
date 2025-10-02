#include "quantum.h"
#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "transactions.h"

enum layer_names {
    _COLEMAKDH,
    _FARSI,
    _COLEMAKDH_OVERLAY,
    NUM,
    FUN,
    SYM,
    NAV,
    MOS,
    MED,
    BLOCK_LEFT,
    BLOCK_RIGHT,
    _JOYSTICK,
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

#define MOD_MASK_RIGHT (0xF0)
#define MOD_MASK_LEFT (0x0F)

enum custom_keycodes {
    MY_MENU = SAFE_RANGE,
    MY_UP,
    MY_DOWN,
    MY_LEFT,
    MY_RIGHT,
    MY_SELECT,
};

#define GET_MOD_FROM_TAP_HOLD(tap_hold_keycode) (((tap_hold_keycode) & 0x0F00) >> 8)
#define GET_LAYER_FROM_TAP_HOLD(tap_hold_keycode) (((tap_hold_keycode) & 0x0F00) >> 8)
#define GET_KEYCODE_FROM_TAP_HOLD(tap_hold_keycode) ((tap_hold_keycode) & 0xFF)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  //,--------------+--------------+--------------+--------------+--------------+--------------.  .--------------+--------------+--------------+--------------+--------------+--------------.
  //    XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,
  //|--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------|
  //    XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,
  //`--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------'
  //                   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,
  //               `--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------`
  //                                  XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX
  //                              `--------------+--------------+--------------+--------------'  `--------------+--------------+--------------+--------------'

  //,--------------+--------------+--------------+--------------+--------------+--------------.  .--------------+--------------+--------------+--------------+--------------+--------------.
  //    _______    ,   _______    ,   _______    ,   _______    ,   _______    ,   _______    ,      _______    ,   _______    ,   _______    ,   _______    ,   _______    ,   _______    ,
  //|--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------|
  //    _______    ,   _______    ,   _______    ,   _______    ,   _______    ,   _______    ,      _______    ,   _______    ,   _______    ,   _______    ,   _______    ,   _______    ,
  //`--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------'
  //                   _______    ,   _______    ,   _______    ,   _______    ,   _______    ,      _______    ,   _______    ,   _______    ,   _______    ,   _______    ,
  //               `--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------`
  //                                  _______    ,   _______    ,   _______    ,   _______    ,      _______    ,   _______    ,   _______    ,   _______
  //                              `--------------+--------------+--------------+--------------'  `--------------+--------------+--------------+-------------'

  [_COLEMAKDH] = LAYOUT(
  //,--------------+--------------+--------------+--------------+--------------+--------------.  .--------------+--------------+--------------+--------------+--------------+--------------.
         KC_GRV    ,     KC_Q     ,     KC_W     ,     KC_F     ,     KC_P     ,     KC_B     ,        KC_J     ,     KC_L     ,     KC_U     ,     KC_Y     ,   KC_DQUO    ,   KC_UNDS    ,
  //|--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------|
        KC_SLSH    ,   MT_LGUI_A  ,   MT_LALT_R  ,   MT_LCTL_S  ,   MT_LSFT_T  ,     KC_G     ,        KC_M     ,   MT_RSFT_N  ,   MT_RCTL_E  ,   MT_RALT_I  ,   MT_RGUI_O  ,   KC_EQUAL   ,
  //`--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------'
                         KC_Z     ,     KC_X     ,     KC_C     ,     KC_D     ,     KC_V     ,        KC_K     ,     KC_H     ,    KC_COMM   ,    KC_DOT    ,   KC_SCLN    ,
  //               `--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------`
                                       KC_F13    ,  LT_MED_ESC  ,  LT_NAV_SPC  ,  LT_MOS_TAB  ,     LT_NUM_ENT  , LT_SYM_BSPC  ,  LT_FUN_DEL  ,   MY_MENU
  //                              `--------------+--------------+--------------+--------------'  `--------------+--------------+--------------+--------------'
  ),
  [_FARSI] = LAYOUT(
  //,--------------+--------------+--------------+--------------+--------------+--------------.  .--------------+--------------+--------------+--------------+--------------+--------------.
         KC_GRV    ,     KC_Q     ,     KC_W     ,     KC_E     ,     KC_R     ,     KC_T     ,        KC_Y     ,     KC_U     ,     KC_I     ,     KC_O     ,     KC_P     ,   KC_UNDS    ,
  //|--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------|
        KC_SLSH    ,   MT_LGUI_A  ,   MT_LALT_S  ,   MT_LCTL_D  ,   MT_LSFT_F  ,     KC_G     ,        KC_H     ,   MT_RSFT_J  ,   MT_RCTL_K  ,   MT_RALT_L  , MT_RGUI_SCLN ,   KC_EQUAL   ,
  //`--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------'
                         KC_Z     ,     KC_X     ,     KC_C     ,     KC_V     ,     KC_B     ,        KC_N     ,     KC_M     ,   KC_COMM    ,    KC_DOT    ,   KC_QUOTE   ,
  //               `--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------`
                                       KC_F13    ,  LT_MED_ESC  ,  LT_NAV_SPC  ,  LT_MOS_TAB  ,     LT_NUM_ENT  , LT_SYM_BSPC  ,  LT_FUN_DEL  ,   MY_MENU
  //                              `--------------+--------------+--------------+--------------'  `--------------+--------------+--------------+--------------'
  ),
  [_COLEMAKDH_OVERLAY] = LAYOUT(
  //,--------------+--------------+--------------+--------------+--------------+--------------.  .--------------+--------------+--------------+--------------+--------------+--------------.
         KC_GRV    ,     KC_Q     ,     KC_W     ,     KC_F     ,     KC_P     ,     KC_B     ,        KC_J     ,     KC_L     ,     KC_U     ,     KC_Y     ,   KC_DQUO    ,   KC_UNDS    ,
  //|--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------|
        KC_SLSH    ,   MT_LGUI_A  ,   MT_LALT_R  ,   MT_LCTL_S  ,   MT_LSFT_T  ,     KC_G     ,        KC_M     ,   MT_RSFT_N  ,   MT_RCTL_E  ,   MT_RALT_I  ,   MT_RGUI_O  ,   KC_EQUAL   ,
  //`--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------'
                         KC_Z     ,     KC_X     ,     KC_C     ,     KC_D     ,     KC_V     ,        KC_K     ,     KC_H     ,    KC_COMM   ,    KC_DOT    ,   KC_SCLN    ,
  //               `--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------`
                                       KC_F13    ,  LT_MED_ESC  ,  LT_NAV_SPC  ,  LT_MOS_TAB  ,     LT_NUM_ENT  , LT_SYM_BSPC  ,  LT_FUN_DEL  ,   MY_MENU
  //                              `--------------+--------------+--------------+--------------'  `--------------+--------------+--------------+--------------'
  ),
  [NUM] = LAYOUT(
  //,--------------+--------------+--------------+--------------+--------------+--------------.  .--------------+--------------+--------------+--------------+--------------+--------------.
        XXXXXXX    ,   XXXXXXX    ,     KC_9     ,     KC_8     ,     KC_7     ,   XXXXXXX    ,      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,
  //|--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------|
        XXXXXXX    ,   XXXXXXX    ,     KC_6     ,     KC_5     ,     KC_4     ,   XXXXXXX    ,      XXXXXXX    ,   KC_RSFT    ,   KC_RCTL    ,   KC_RALT    ,   KC_RGUI    ,   XXXXXXX    ,
  //`--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------'
                       XXXXXXX    ,     KC_3     ,     KC_2     ,     KC_1     ,   XXXXXXX    ,      XXXXXXX    ,   XXXXXXX    ,   KC_COMM    ,    KC_DOT    ,   XXXXXXX    ,
  //               `--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------`
                                      XXXXXXX    ,   XXXXXXX    ,     KC_0     ,   XXXXXXX    ,      _______    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX
  //                              `--------------+--------------+--------------+--------------'  `--------------+--------------+--------------+--------------'
  ),
  [SYM] = LAYOUT(
  //,--------------+--------------+--------------+--------------+--------------+--------------.  .--------------+--------------+--------------+--------------+--------------+--------------.
         KC_DLR    ,   KC_PERC    ,    KC_AT     ,    KC_LT     ,    KC_GT     ,   KC_PIPE    ,      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,
  //|--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------|
        XXXXXXX    ,   KC_ASTR    ,   XXXXXXX    ,   KC_LCBR    ,   KC_RCBR    ,   KC_AMPR    ,      XXXXXXX    ,   KC_RSFT    ,   KC_RCTL    ,   KC_RALT    ,   KC_RGUI    ,   XXXXXXX    ,
  //`--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------'
                       KC_CIRC    ,   XXXXXXX    ,   KC_LBRC    ,   KC_RBRC    ,   KC_HASH    ,      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,
  //               `--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------`
                                      XXXXXXX    ,   KC_EXLM    ,   XXXXXXX    ,   KC_QUES    ,      XXXXXXX    ,   _______    ,   XXXXXXX    ,   XXXXXXX
  //                              `--------------+--------------+--------------+--------------'  `--------------+--------------+--------------+--------------'
  ),
  [FUN] = LAYOUT(
  //,--------------+--------------+--------------+--------------+--------------+--------------.  .--------------+--------------+--------------+--------------+--------------+--------------.
        XXXXXXX    ,    KC_F12    ,     KC_F9    ,     KC_F8    ,     KC_F7    ,   XXXXXXX    ,      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,
  //|--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------|
        XXXXXXX    ,    KC_F11    ,     KC_F6    ,     KC_F5    ,     KC_F4    ,   KC_PSCR    ,      XXXXXXX    ,   KC_RSFT    ,   KC_RCTL    ,   KC_RALT    ,   KC_RGUI    ,   XXXXXXX    ,
  //`--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------'
                        KC_F10    ,     KC_F3    ,     KC_F2    ,     KC_F1    ,   XXXXXXX    ,      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,
  //               `--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------`
                                      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,      XXXXXXX    ,   XXXXXXX    ,   _______    ,   XXXXXXX
  //                              `--------------+--------------+--------------+--------------'  `--------------+--------------+--------------+--------------'
  ),
  [NAV] = LAYOUT(
  //,--------------+--------------+--------------+--------------+--------------+--------------.  .--------------+--------------+--------------+--------------+--------------+--------------.
        XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,
  //|--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------|
        XXXXXXX    ,   KC_LGUI    ,   KC_LALT    ,   KC_LCTL    ,   KC_LSFT    ,   XXXXXXX    ,      KC_LEFT    ,   KC_DOWN    ,    KC_UP     ,   KC_RGHT    ,   XXXXXXX    ,   XXXXXXX    ,
  //`--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------'
                       XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,      KC_HOME    ,   KC_PGDN    ,   KC_PGUP    ,   XXXXXXX    ,    KC_END    ,
  //               `--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------`
                                      XXXXXXX    ,   XXXXXXX    ,   _______    ,   XXXXXXX    ,      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX
  //                              `--------------+--------------+--------------+--------------'  `--------------+--------------+--------------+--------------'
  ),
  [MOS] = LAYOUT(
  //,--------------+--------------+--------------+--------------+--------------+--------------.  .--------------+--------------+--------------+--------------+--------------+--------------.
        XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,
  //|--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------|
        XXXXXXX    ,   KC_LGUI    ,   KC_LALT    ,   KC_LCTL    ,   KC_LSFT    ,   XXXXXXX    ,      MS_LEFT    ,   MS_DOWN    ,    MS_UP     ,   MS_RGHT    ,   XXXXXXX    ,   XXXXXXX    ,
  //`--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------'
                       XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,      MS_WHLL    ,   MS_WHLD    ,   MS_WHLU    ,   MS_WHLR    ,   XXXXXXX    ,
  //               `--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------`
                                      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   _______    ,      MS_BTN2    ,   MS_BTN1    ,   MS_BTN3    ,   XXXXXXX
  //                              `--------------+--------------+--------------+--------------'  `--------------+--------------+--------------+--------------'
  ),
  [MED] = LAYOUT(
  //,--------------+--------------+--------------+--------------+--------------+--------------.  .--------------+--------------+--------------+--------------+--------------+--------------.
        XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,
  //|--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------|
        XXXXXXX    ,   KC_LGUI    ,   KC_LALT    ,   KC_LCTL    ,   KC_LSFT    ,   XXXXXXX    ,      KC_MPRV    ,   KC_VOLD    ,   KC_VOLU    ,   KC_MNXT    ,   XXXXXXX    ,   XXXXXXX    ,
  //`--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------'
                       XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,
  //               `--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------`
                                      XXXXXXX    ,   _______    ,   XXXXXXX    ,   XXXXXXX    ,      XXXXXXX    ,   KC_MPLY    ,   KC_MUTE    ,   XXXXXXX
  //                              `--------------+--------------+--------------+--------------'  `--------------+--------------+--------------+--------------'
  ),
  [_MENU] = LAYOUT(
  //,--------------+--------------+--------------+--------------+--------------+--------------.  .--------------+--------------+--------------+--------------+--------------+--------------.
        XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,    XXXXXXX   ,   XXXXXXX    ,
  //|--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------|
        XXXXXXX    ,   XXXXXXX    ,   MY_LEFT    ,    MY_UP     ,   MY_DOWN    ,   MY_RIGHT   ,      MY_LEFT    ,   MY_DOWN    ,    MY_UP     ,   MY_RIGHT   ,    XXXXXXX   ,   XXXXXXX    ,
  //`--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------'
                       XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,    XXXXXXX   ,
  //               `--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------`
                                      XXXXXXX    ,   XXXXXXX    ,  MY_SELECT   ,   XXXXXXX    ,      XXXXXXX    ,  MY_SELECT   ,   XXXXXXX    ,   MY_MENU
  //                              `--------------+--------------+--------------+--------------'  `--------------+--------------+--------------+--------------'
  ),
  [BLOCK_LEFT] = LAYOUT(
  //,--------------+--------------+--------------+--------------+--------------+--------------.  .--------------+--------------+--------------+--------------+--------------+--------------.
        XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,      _______    ,   _______    ,   _______    ,   _______    ,   _______    ,   _______    ,
  //|--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------|
        XXXXXXX    ,   KC_LGUI    ,   KC_LALT    ,   KC_LCTL    ,   KC_LSFT    ,   XXXXXXX    ,      _______    ,   _______    ,   _______    ,   _______    ,   _______    ,   _______    ,
  //`--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------'
                       XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,      _______    ,   _______    ,   _______    ,   _______    ,   _______    ,
  //               `--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------`
                                      _______    ,   _______    ,   _______    ,   _______    ,      _______    ,   _______    ,   _______    ,   _______
  //                              `--------------+--------------+--------------+--------------'  `--------------+--------------+--------------+--------------'
  ),
  [BLOCK_RIGHT] = LAYOUT(
  //,--------------+--------------+--------------+--------------+--------------+--------------.  .--------------+--------------+--------------+--------------+--------------+--------------.
        _______    ,   _______    ,   _______    ,   _______    ,   _______    ,   _______    ,      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,
  //|--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------|
        _______    ,   _______    ,   _______    ,   _______    ,   _______    ,   _______    ,      XXXXXXX    ,   KC_RSFT    ,   KC_RCTL    ,   KC_RALT    ,   KC_RGUI    ,   XXXXXXX    ,
  //`--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------'
                       _______    ,   _______    ,   _______    ,   _______    ,   _______    ,      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,
  //               `--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------`
                                      _______    ,   _______    ,   _______    ,   _______    ,      _______    ,   _______    ,   _______    ,   _______
  //                              `--------------+--------------+--------------+--------------'  `--------------+--------------+--------------+--------------'
  ),
  [_JOYSTICK] = LAYOUT(
  //,--------------+--------------+--------------+--------------+--------------+--------------.  .--------------+--------------+--------------+--------------+--------------+--------------.
          JS_13    ,     JS_2     ,   XXXXXXX    ,   XXXXXXX    ,     JS_11    ,    XXXXXXX   ,       XXXXXXX   ,     JS_27    ,   XXXXXXX    ,   XXXXXXX    ,     JS_18    ,     JS_29    ,
  //|--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------|
          JS_14    ,     JS_1     ,     JS_0     ,   XXXXXXX    ,   XXXXXXX    ,     JS_12    ,        JS_28    ,   XXXXXXX    ,   XXXXXXX    ,     JS_16    ,     JS_17    ,     JS_30    ,
  //`--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------'
                         JS_15    ,     JS_3     ,     JS_10    ,     JS_9     ,     JS_8     ,        JS_24    ,     JS_25    ,     JS_26    ,     JS_19    ,     JS_31    ,
  //               `--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------`
                                        JS_7     ,     JS_6     ,     JS_5     ,     JS_4     ,        JS_20    ,     JS_21    ,     JS_22   ,     JS_23
  //                              `--------------+--------------+--------------+--------------'  `--------------+--------------+--------------+--------------'
  )
};
// clang-format on

const key_override_t override_swap_qoute_and_double_qoute     = ko_make_basic(MOD_MASK_SHIFT, KC_DQUO, KC_QUOT);
const key_override_t override_shift_slash_is_back_slash       = ko_make_basic(MOD_MASK_SHIFT, KC_SLSH, KC_BSLS);
const key_override_t override_swap_minus_and_underscore       = ko_make_basic(MOD_MASK_SHIFT, KC_UNDS, KC_MINUS);
const key_override_t override_shift_comma_is_left_parenthesis = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_LPRN);
const key_override_t override_shift_dot_is_right_parenthesis  = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_RPRN);
const key_override_t override_persian_shift_kaf_is_gaf        = ko_make_with_layers(MOD_MASK_SHIFT, KC_SCLN, KC_QUOT, 1 << _FARSI);
const key_override_t override_persian_shift_khe_is_jim        = ko_make_with_layers(MOD_MASK_SHIFT, KC_O, KC_LBRC, 1 << _FARSI);
const key_override_t override_persian_shift_he_is_che         = ko_make_with_layers(MOD_MASK_SHIFT, KC_P, KC_RBRC, 1 << _FARSI);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
    &override_swap_qoute_and_double_qoute, &override_shift_slash_is_back_slash, &override_swap_minus_and_underscore, &override_shift_dot_is_right_parenthesis, &override_shift_comma_is_left_parenthesis, &override_persian_shift_kaf_is_gaf, &override_persian_shift_he_is_che, &override_persian_shift_khe_is_jim,
};

enum OLED_MODE {
    OLED_OFF,
    OLED_MENU,
    OLED_PREFS,
    OLED_JOYSTICK,
    OLED_BOOTLOADER,
};
enum OLED_MENU {
    MENU_JOYSTICK,
    MENU_PREFS,
    MENU_FLASH,

    NUMBER_OF_MENU_ITEMS,
};
enum OLED_PREFS {
    PREFS_TAP_TERM,

    NUMBER_OF_PREFS_ITEMS,
};

enum OS_TYPES {
    OS_UNKNOWN = 0,
    OS_WINDOWS = 1,
    OS_MACOS   = 2,
    OS_LINUX   = 3,
};

enum KEYBOARD_LAYOUT {
    LAYOUT_ENGLISH = 0,
    LAYOUT_FARSI   = 1,
};

typedef union {
    uint16_t raw;
    struct {
        union {
            uint8_t raw;
            struct {
                unsigned mode : 3;
                unsigned menu_index : 2;
                unsigned prefs_index : 2;
            };
        } oled;
        union {
            uint8_t raw;
            struct {
                unsigned os_type : 2;
                unsigned active_layout : 2;
            };
        } hid;
    };
} state_t;

state_t state = {0x00};

typedef union {
    uint32_t raw;
    struct {
        uint8_t tap_term;
    };
} user_config_t;

user_config_t user_config;

void raw_hid_receive(uint8_t *data, uint8_t length) {
    state.hid.raw = *(uint8_t *)data;
}

void setup_config(void) {
    g_tapping_term = user_config.tap_term;
    if (is_keyboard_master()) transaction_rpc_send(USER_CONFIG_SYNC, sizeof(user_config.raw), &user_config.raw);
}

void user_config_sync_slave_handler(uint8_t in_buflen, const void *sync_data, uint8_t out_buflen, void *out_data) {
    user_config.raw = *(uint32_t *)sync_data;
    eeconfig_update_user(user_config.raw);
    setup_config();
}

void state_sync_slave_handler(uint8_t in_buflen, const void *sync_data, uint8_t out_buflen, void *out_data) {
    state.raw = *(uint16_t *)sync_data;
}

void keyboard_post_init_user() {
    user_config.raw = eeconfig_read_user();
    setup_config();
    transaction_register_rpc(USER_CONFIG_SYNC, user_config_sync_slave_handler);
    transaction_register_rpc(STATE_SYNC, state_sync_slave_handler);
}

void eeconfig_init_user() {
    user_config.tap_term = TAPPING_TERM;
}

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (get_mods() & MOD_MASK_RIGHT) {
        layer_on(BLOCK_RIGHT);
    } else {
        layer_off(BLOCK_RIGHT);
    }

    if (get_mods() & MOD_MASK_LEFT) {
        layer_on(BLOCK_LEFT);
    } else {
        layer_off(BLOCK_LEFT);
    }

    if (get_mods() & ~MOD_MASK_SHIFT) {
        state.oled.mode = OLED_JOYSTICK;
        if (IS_LAYER_ON(_FARSI)) {
            layer_on(_COLEMAKDH_OVERLAY);
        }
    }
    else {
        state.oled.mode = OLED_OFF;
        layer_off(_COLEMAKDH_OVERLAY);
    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT_NUM_ENT:
        case LT_SYM_BSPC:
        case LT_FUN_DEL:
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
            if (!record->event.pressed && state.hid.os_type == OS_UNKNOWN && get_mods() & MOD_BIT(KC_RGUI)) {
                if (state.hid.active_layout == LAYOUT_ENGLISH) {
                    state.hid.active_layout = LAYOUT_FARSI;
                } else {
                    state.hid.active_layout = LAYOUT_ENGLISH;
                }
            }
        case LT_MOS_TAB:
        case LT_MED_ESC:
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
            if (get_mods() & MOD_BIT(KC_RSFT)) break;
        case MT_LCTL_S:
        case MT_LALT_R:
        case MT_LGUI_A:
        case MT_LCTL_D:
        case MT_LALT_S:
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
            if (get_mods() & MOD_BIT(KC_LSFT)) break;
        case MT_RCTL_E:
        case MT_RALT_I:
        case MT_RGUI_O:
        case MT_RCTL_K:
        case MT_RALT_L:
        case MT_RGUI_SCLN:
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
            if (!record->event.pressed) {
                switch (state.oled.mode) {
                    case OLED_MENU:
                        set_single_default_layer(_COLEMAKDH);
                        state.oled.mode = OLED_OFF;
                        break;
                    case OLED_PREFS:
                        set_single_default_layer(_MENU);
                        state.oled.prefs_index = 0;
                        state.oled.mode        = OLED_MENU;
                        break;
                    default:
                        set_single_default_layer(_MENU);
                        state.oled.menu_index = 0;
                        state.oled.mode       = OLED_MENU;
                        break;
                }
            }
            break;
        case MY_DOWN:
            if (!record->event.pressed) {
                if (state.oled.mode == OLED_MENU) {
                    state.oled.menu_index = (state.oled.menu_index + 1) % NUMBER_OF_MENU_ITEMS;
                } else if (state.oled.mode == OLED_PREFS) {
                    state.oled.prefs_index = (state.oled.prefs_index + 1) % NUMBER_OF_PREFS_ITEMS;
                }
            }
            break;
        case MY_UP:
            if (!record->event.pressed) {
                if (state.oled.mode == OLED_MENU) {
                    if (state.oled.menu_index == 0)
                        state.oled.menu_index = NUMBER_OF_MENU_ITEMS - 1;
                    else
                        state.oled.menu_index = (state.oled.menu_index - 1) % NUMBER_OF_MENU_ITEMS;
                } else if (state.oled.mode == OLED_PREFS) {
                    if (state.oled.prefs_index == 0)
                        state.oled.prefs_index = NUMBER_OF_PREFS_ITEMS - 1;
                    else
                        state.oled.prefs_index = (state.oled.prefs_index - 1) % NUMBER_OF_PREFS_ITEMS;
                }
            }
            break;
        case MY_LEFT:
            if (record->event.pressed || state.oled.mode != OLED_PREFS) return false;
            if (state.oled.prefs_index == PREFS_TAP_TERM) {
                user_config.tap_term = (user_config.tap_term / 5 * 5) - 5;
            }

            eeconfig_update_user(user_config.raw);
            setup_config();
            break;
        case MY_RIGHT:
            if (record->event.pressed || state.oled.mode != OLED_PREFS) return false;
            user_config.tap_term = (user_config.tap_term / 5 * 5) + 5;
            eeconfig_update_user(user_config.raw);
            setup_config();
            break;
        case MY_SELECT:
            if (!record->event.pressed) {
                switch (state.oled.menu_index) {
                    case MENU_JOYSTICK:
                        set_single_default_layer(_JOYSTICK);
                        state.oled.mode = OLED_JOYSTICK;
                        break;
                    case MENU_PREFS:
                        set_single_default_layer(_MENU);
                        state.oled.mode        = OLED_PREFS;
                        state.oled.prefs_index = 0;
                        break;
                }
            }
            break;
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
            return g_tapping_term * 1.2;
        default:
            return g_tapping_term;
    }
}

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

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270; // flips the display 180 degrees if offhand
}

bool oled_task_user(void) {
    oled_clear();
    switch (state.oled.mode) {
        case OLED_OFF:
            break;
        case OLED_MENU:
            if (!is_keyboard_master()) {
                switch (state.hid.os_type) {
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
                switch (state.hid.active_layout) {
                    case LAYOUT_ENGLISH:
                        oled_write_P(PSTR("\x5F\x10\x19\x12\x5F"), false);
                        break;
                    case LAYOUT_FARSI:
                        oled_write_P(PSTR("\x5F\x11\x0C\x1D\x5F"), false);
                        break;
                }
            } else {
                oled_write_P(PSTR("\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F"), state.oled.menu_index == MENU_JOYSTICK);
                oled_write_P(PSTR("\x5F\x15\x1A\x24\x5F"), state.oled.menu_index == MENU_JOYSTICK);
                oled_write_P(PSTR("\x1E\x1F\x14\x0E\x16"), state.oled.menu_index == MENU_JOYSTICK);
                oled_write_P(PSTR("\x5F\x26\x27\x28\x5F\x29\x2A\x2B\x2C\x2D\x5F\x2E\x2F\x30\x5F"), state.oled.menu_index == MENU_PREFS);
                oled_write_P(PSTR("\x1B\x1D\x10\x11\x1E"), state.oled.menu_index == MENU_PREFS);
                oled_advance_page(false);
                oled_write_P(PSTR("\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E"), state.oled.menu_index == MENU_FLASH);
                oled_write_P(PSTR("\x11\x17\x0C\x1E\x13"), state.oled.menu_index == MENU_FLASH);
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
                oled_write_P(PSTR("\x5F\x1F\x0C\x1B\x5F"), state.oled.prefs_index == PREFS_TAP_TERM);
                oled_write_P(PSTR("\x1F\x10\x1D\x18\x5F"), state.oled.prefs_index == PREFS_TAP_TERM);
                state.oled.prefs_index == PREFS_TAP_TERM ? oled_write_P(PSTR("\x2C"), false) : oled_advance_char();
                user_config.tap_term >= 100 ? oled_write_char((user_config.tap_term / 100), false) : oled_write_char(0, false);
                user_config.tap_term >= 10 ? oled_write_char((user_config.tap_term / 10) % 10, false) : oled_write_char(0, false);
                oled_write_char(user_config.tap_term % 10, false);
                state.oled.prefs_index == PREFS_TAP_TERM ? oled_write_P(PSTR("\x2A"), false) : oled_advance_char();
            }
            break;
    }
    return false;
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
            state.oled.mode    = OLED_BOOTLOADER;
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
            transaction_rpc_send(STATE_SYNC, sizeof(state.raw), &state.raw);
            last_sync = timer_read32();
        }
        set_single_default_layer(state.hid.active_layout);
    }
}
