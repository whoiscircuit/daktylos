#include "oled_driver.h"
#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "transactions.h"

enum layer_names {
    _COLEMAKDH,
    // _QWERTY,
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
                                      MY_MENU    ,  LT_MED_ESC  ,  LT_NAV_SPC  ,  LT_MOS_TAB  ,     LT_NUM_ENT  , LT_SYM_BSPC  ,  LT_FUN_DEL  ,   MY_MENU
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
                                      MY_MENU    ,   XXXXXXX    ,  MY_SELECT   ,   XXXXXXX    ,      XXXXXXX    ,  MY_SELECT   ,   XXXXXXX    ,   MY_MENU
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
  ),
};
// clang-format on

const key_override_t override_swap_qoute_and_double_qoute     = ko_make_basic(MOD_MASK_SHIFT, KC_DQUO, KC_QUOT);
const key_override_t override_shift_slash_is_back_slash       = ko_make_basic(MOD_MASK_SHIFT, KC_SLSH, KC_BSLS);
const key_override_t override_swap_minus_and_underscore       = ko_make_basic(MOD_MASK_SHIFT, KC_UNDS, KC_MINUS);
const key_override_t override_shift_comma_is_left_parenthesis = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_LPRN);
const key_override_t override_shift_dot_is_right_parenthesis  = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_RPRN);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
    &override_swap_qoute_and_double_qoute, &override_shift_slash_is_back_slash, &override_swap_minus_and_underscore, &override_shift_dot_is_right_parenthesis, &override_shift_comma_is_left_parenthesis,
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
                unsigned os_type :2;
            };
        } hid;
    };
} state_t;

state_t state = {0x00};

struct MenuItem {
    const char icon[16];
    const char top_title[6];
    const char bottom_title[6];
};
struct PrefsItem {
    const char top_title[6];
    const char bottom_title[6];
    uint8_t   *value;
};

typedef union {
    uint32_t raw;
    struct {
        uint8_t tap_term;
    };
} user_config_t;

user_config_t user_config;


void raw_hid_receive(uint8_t *data, uint8_t length){
    state.hid.raw = *(uint8_t*)data;
    transaction_rpc_send(STATE_SYNC, sizeof(state.raw), &state.raw);
}


void setup_config(void){
    g_tapping_term  = user_config.tap_term;
    if(is_keyboard_master()) transaction_rpc_send(USER_CONFIG_SYNC, sizeof(user_config.raw), &user_config.raw);
}

void user_config_sync_slave_handler(uint8_t in_buflen, const void *sync_data, uint8_t out_buflen, void *out_data) {
    user_config.raw = *(uint32_t *)sync_data;
    eeconfig_update_user(user_config.raw);
    setup_config();
}

void state_sync_slave_handler(uint8_t in_buflen, const void *sync_data, uint8_t out_buflen, void *out_data) {
    state.raw = *(uint16_t *)sync_data;
    state.oled.mode = OLED_JOYSTICK;
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

static const struct PrefsItem PROGMEM prefs_items[] = {
    [PREFS_TAP_TERM] = {"\x5F\x1F\x0C\x1B\x5F", "\x1F\x10\x1D\x18\x5F", &user_config.tap_term},
};

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
            if (get_mods() & MOD_BIT(KC_RSFT)) break;
        case MT_LCTL_S:
        case MT_LALT_R:
        case MT_LGUI_A:
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
            if (get_mods() & MOD_BIT(KC_LSFT)) break;
        case MT_RCTL_E:
        case MT_RALT_I:
        case MT_RGUI_O:
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
                        state.oled.mode       = OLED_MENU;
                        break;
                    default:
                        set_single_default_layer(_MENU);
                        state.oled.menu_index = 0;
                        state.oled.mode      = OLED_MENU;
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
            *prefs_items[state.oled.prefs_index].value = (*prefs_items[state.oled.prefs_index].value / 5 * 5) - 5;
            eeconfig_update_user(user_config.raw);
            setup_config();
            break;
        case MY_RIGHT:
            if (record->event.pressed || state.oled.mode != OLED_PREFS) return false;
            *prefs_items[state.oled.prefs_index].value = (*prefs_items[state.oled.prefs_index].value / 5 * 5) + 5;
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
                        state.oled.mode       = OLED_PREFS;
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
            return g_tapping_term * 1.5;
        case MT_RCTL_E:
        case MT_LCTL_S:
            return g_tapping_term * 0.8;
        case MT_RSFT_N:
        case MT_LSFT_T:
            return g_tapping_term * 0.7;
        default:
            return g_tapping_term;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT_RSFT_N:
        case MT_LSFT_T:
            return g_tapping_term * 1.2;
        case MT_RCTL_E:
        case MT_LCTL_S:
            return g_tapping_term * 0.8;
        case LT_NAV_SPC:
        case LT_SYM_BSPC:
            return g_tapping_term;
        default:
            return g_tapping_term * 0.8;
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
    static uint8_t i = 0;
    static const struct MenuItem PROGMEM menu_items[] = {
        [MENU_JOYSTICK] = {"\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F", "\x5F\x15\x1A\x24\x5F", "\x1E\x1F\x14\x0E\x16"},
        [MENU_PREFS]    = {"\x5F\x26\x27\x28\x5F\x29\x2A\x2B\x2C\x2D\x5F\x2E\x2F\x30\x5F", "\x1B\x1D\x10\x11\x1E", "\x5F\x5F\x5F\x5F\x5F"},
        [MENU_FLASH]    = {"\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E", "\x11\x17\x0C\x1E\x13", "\x5F\x5F\x5F\x5F\x5F"},
    };
    oled_clear();
    if (!is_keyboard_master()){
        switch (state.hid.os_type) {
            case 0x03:
                oled_write_P(PSTR("\x57\x58"),false);
                oled_advance_page(false);
                oled_write_P(PSTR("\x59\x5A"),false);
            break;
        }
        return false;
    };
    switch (state.oled.mode) {
        case OLED_OFF:
            break;
        case OLED_MENU:
            for (i = (state.oled.menu_index / 3) * 3; i < (state.oled.menu_index / 3) * 3 + 3; i++) {
                if (i >= NUMBER_OF_MENU_ITEMS) break;
                oled_write_P(menu_items[i].icon, state.oled.menu_index == i);
                oled_write_P(menu_items[i].top_title, state.oled.menu_index == i);
                oled_write_P(menu_items[i].bottom_title, state.oled.menu_index == i);
            }
            break;
        case OLED_BOOTLOADER:
            oled_set_cursor(0, 4);
            oled_write_P(menu_items[MENU_FLASH].icon, false);
            oled_advance_page(true);
            oled_write_P(menu_items[MENU_FLASH].top_title, false);
            break;
        case OLED_JOYSTICK:
            oled_set_cursor(0, 4);
            oled_write_P(menu_items[MENU_JOYSTICK].icon, false);
            oled_write_P(menu_items[MENU_JOYSTICK].top_title, false);
            oled_write_P(menu_items[MENU_JOYSTICK].bottom_title, false);
            break;
        case OLED_PREFS:
            for (i = (state.oled.prefs_index / 4) * 4; i < (state.oled.prefs_index / 4) * 4 + 4; i++) {
                if (i >= NUMBER_OF_PREFS_ITEMS) break;
                oled_write_P(prefs_items[i].top_title, state.oled.prefs_index == i);
                oled_write_P(prefs_items[i].bottom_title, state.oled.prefs_index == i);
                state.oled.prefs_index == i ? oled_write_P(PSTR("\x2C"), false) : oled_advance_char();
                if (*prefs_items[i].value >= 100)
                    oled_write_char((char)(*prefs_items[i].value / 100), false);
                else
                    oled_write_char((char)0, false);
                if (*prefs_items[i].value >= 10)
                    oled_write_char((char)((*prefs_items[i].value / 10) % 10), false);
                else
                    oled_write_char((char)0, false);
                oled_write_char((char)(*prefs_items[i].value % 10), false);
                state.oled.prefs_index == i ? oled_write_P(PSTR("\x2A"), false) : oled_advance_char();
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
