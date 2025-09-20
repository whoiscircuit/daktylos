#include QMK_KEYBOARD_H

enum layer_names {
    _COLEMAKDH,
    // _QWERTY,
    // _GAMING,
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

static const uint8_t MOD_MASK_RIGHT = 0xF0;
static const uint8_t MOD_MASK_LEFT  = 0x0F;

enum custom_keycodes {
    MY_MENU = SAFE_RANGE,
    MY_UP,
    MY_DOWN,
    MY_LEFT,
    MY_RIGHT,
    MY_SELECT
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
        XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,KC_SCROLL_LOCK,   XXXXXXX    ,
  //|--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------|
        XXXXXXX    ,   XXXXXXX    ,   MY_LEFT    ,    MY_UP     ,   MY_DOWN    ,   MY_RIGHT   ,      MY_LEFT    ,   MY_DOWN    ,    MY_UP     ,   MY_RIGHT   , KC_CAPS_LOCK ,   XXXXXXX    ,
  //`--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------'
                       XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,      XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,  KC_NUM_LOCK ,
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
          JS_14    ,     JS_3     ,   XXXXXXX    ,   XXXXXXX    ,     JS_12    ,    XXXXXXX   ,       XXXXXXX   ,     JS_12    ,   XXXXXXX    ,   XXXXXXX    ,     JS_3     ,     JS_14    ,
  //|--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------|
          JS_15    ,     JS_2     ,     JS_1     ,   XXXXXXX    ,   XXXXXXX    ,     JS_13    ,        JS_13    ,   XXXXXXX    ,   XXXXXXX    ,     JS_1     ,     JS_2     ,     JS_15    ,
  //`--------------+--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------+--------------'
                         JS_16    ,     JS_4     ,     JS_10    ,     JS_9     ,     JS_11    ,        JS_11    ,      JS_9    ,     JS_10    ,     JS_4     ,     JS_16    ,
  //               `--------------+--------------+--------------+--------------+--------------|  |--------------+--------------+--------------+--------------+--------------`
                                        JS_8     ,     JS_6     ,     JS_5     ,     JS_7     ,        JS_7     ,     JS_5     ,     JS_6     ,     JS_8
  //                              `--------------+--------------+--------------+--------------'  `--------------+--------------+--------------+--------------'
  )
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

enum OLED_STATE {
    OLED_OFF,
    OLED_MENU,
    OLED_PREFS,
    OLED_JOYSTICK,
    OLED_BOOTLOADER
};
enum OLED_MENU {
    MENU_GAME_MODE,
    MENU_JOYSTICK,
    MENU_PREFS,
    MENU_FLASH
};
struct {
    unsigned state : 3;
    unsigned menu_index : 2;
} oled_data = {OLED_OFF,MENU_GAME_MODE};

static uint16_t my_boot_timer = 0;
static uint16_t my_boot_hold_timer = 0;
static bool jump_to_bootloader = false;

struct MenuItem {
    char icon[16];
    char top_title[6];
    char bottom_tittle[6];
};

static const struct MenuItem PROGMEM menu_items[] = {
    [MENU_GAME_MODE] = {"\x8A\x8B\x8C\x8D\x8E\xAA\xAB\xAC\xAD\xAE\xCA\xCB\xCC\xCD\xCE"," GAME"," MODE"},
    [MENU_JOYSTICK] = {"\x85\x86\x87\x88\x89\xA5\xA6\xA7\xA8\xA9\xC5\xC6\xC7\xC8\xC9"," JOY ","STICK"},
    [MENU_PREFS] = {"\x80\x81\x82\x83\x84\xA0\xA1\xA2\xA3\xA4\xC0\xC1\xC2\xC3\xC4","PREFS","     "},
    [MENU_FLASH] = {"\x8F\x90\x91\x92\x93\xAF\xB0\xB1\xB2\xB3\xCF\xD0\xD1\xD2\xD3","FLASH","     "},
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if(get_mods() & MOD_MASK_RIGHT){
        layer_on(BLOCK_RIGHT);
    }
    else{
        layer_off(BLOCK_RIGHT);
    }
    if(get_mods() & MOD_MASK_LEFT){
        layer_on(BLOCK_LEFT);
    }
    else{
        layer_off(BLOCK_LEFT);
    }
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
            if(get_mods() & MOD_BIT(KC_RSFT)) break;
        case MT_LCTL_S:
        case MT_LALT_R:
        case MT_LGUI_A:
            if (record->event.pressed) {
                if(get_mods() & MOD_MASK_RIGHT){
                    register_code(GET_KEYCODE_FROM_TAP_HOLD(keycode));
                    return false;
                }
            }
            else{
                unregister_code(GET_KEYCODE_FROM_TAP_HOLD(keycode));
                return true;
            }
            break;

        case MT_RSFT_N:
            if(get_mods() & MOD_BIT(KC_LSFT)) break;
        case MT_RCTL_E:
        case MT_RALT_I:
        case MT_RGUI_O:
            if (record->event.pressed) {
                if(get_mods() & MOD_MASK_LEFT){
                    register_code(GET_KEYCODE_FROM_TAP_HOLD(keycode));
                    return false;
                }
            }
            else{
                unregister_code(GET_KEYCODE_FROM_TAP_HOLD(keycode));
                return true;
            }
            break;
        case MY_MENU:
            if(!record->event.pressed){
                if(oled_data.state == OLED_MENU){
                    set_single_default_layer(_COLEMAKDH);
                    oled_data.state = OLED_OFF;
                }
                else{
                    set_single_default_layer(_MENU);
                    oled_data.menu_index = 0;
                    oled_data.state = OLED_MENU;
                }
            }
            break;
        case MY_DOWN:
            if(!record->event.pressed){
                oled_data.menu_index = (oled_data.menu_index + 1) % (sizeof(menu_items)/sizeof(menu_items[0]));
            }
            break;
        case MY_UP:
            if(!record->event.pressed){
                if(oled_data.menu_index == 0) oled_data.menu_index = (sizeof(menu_items)/sizeof(menu_items[0])) - 1;
                else oled_data.menu_index = (oled_data.menu_index - 1) % (sizeof(menu_items)/sizeof(menu_items[0]));
            }
            break;
        case MY_SELECT:
            if(!record->event.pressed){
                switch (oled_data.menu_index) {
                    case MENU_GAME_MODE:
                        break;
                    case MENU_JOYSTICK:
                        set_single_default_layer(_JOYSTICK);
                        oled_data.state = OLED_JOYSTICK;
                        break;
                    case MENU_PREFS:
                        oled_data.state = OLED_PREFS;
                        break;
                }
            }
            break;
    }
    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return g_tapping_term;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT_RSFT_N:
        case MT_LSFT_T:
            return g_tapping_term * 1.2;
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
    return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
}

uint8_t i=0;
bool oled_task_user(void) {
    oled_clear();
    if(!is_keyboard_master()) return false;
    switch(oled_data.state){
        case OLED_OFF:
            break;
        case OLED_MENU:
            for(i = (oled_data.menu_index / 3) * 3;i<(oled_data.menu_index / 3) * 3 + 3;i++){
                if(i>=sizeof(menu_items)/sizeof(menu_items[0])) break;
                oled_write_P(menu_items[i].icon,oled_data.menu_index == i);
                oled_write_P(menu_items[i].top_title,oled_data.menu_index == i);
                oled_write_P(menu_items[i].bottom_tittle,oled_data.menu_index == i);
            }
            break;
        case OLED_BOOTLOADER:
            oled_set_cursor(0,4);
            oled_write_P(menu_items[MENU_FLASH].icon,false);
            oled_advance_page(true);
            oled_write_P(PSTR("FLASH"),false);
            oled_write_P(PSTR(" NOW "),false);
            break;
        case OLED_JOYSTICK:
            oled_write_P(menu_items[MENU_JOYSTICK].icon,false);
            oled_advance_page(true);
        break;
    }
    return false;
}


void matrix_scan_user(void){
    if(jump_to_bootloader && timer_elapsed(my_boot_timer) > 200){
        reset_keyboard();
    }
    // logic for restart and jumping to bootloader based on pressing the two thumb keys
    if((matrix_is_on(7,5) && matrix_is_on(7,3)) || (matrix_is_on(3,3) && matrix_is_on(3,5))){
        if(my_boot_hold_timer == 0){
            my_boot_hold_timer = timer_read();
        }
    }
    else if(my_boot_hold_timer != 0){
        if(timer_elapsed(my_boot_hold_timer) > g_tapping_term * 2){
            oled_data.state = OLED_BOOTLOADER;
            jump_to_bootloader = true;
            my_boot_timer = timer_read();
        }
        else if(timer_elapsed(my_boot_hold_timer) > g_tapping_term / 2){
            soft_reset_keyboard();
        }
        my_boot_hold_timer = 0;
    }
}
