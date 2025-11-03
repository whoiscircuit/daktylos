#include QMK_KEYBOARD_H
#include "key_overrides.h"
#include "keymap.h"

static const key_override_t override_swap_qoute_and_double_qoute     = ko_make_basic(MOD_MASK_SHIFT, KC_DQUO, KC_QUOT);
static const key_override_t override_shift_slash_is_back_slash       = ko_make_basic(MOD_MASK_SHIFT, KC_SLSH, KC_BSLS);
static const key_override_t override_swap_minus_and_underscore       = ko_make_basic(MOD_MASK_SHIFT, KC_UNDS, KC_MINUS);
static const key_override_t override_shift_comma_is_left_parenthesis = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_LPRN);
static const key_override_t override_shift_dot_is_right_parenthesis  = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_RPRN);
static const key_override_t override_persian_shift_kaf_is_gaf        = ko_make_with_layers(MOD_MASK_SHIFT, KC_SCLN, KC_QUOT, 1 << _FARSI);
static const key_override_t override_persian_shift_khe_is_jim        = ko_make_with_layers(MOD_MASK_SHIFT, KC_O, KC_LBRC, 1 << _FARSI);
static const key_override_t override_persian_shift_he_is_che         = ko_make_with_layers(MOD_MASK_SHIFT, KC_P, KC_RBRC, 1 << _FARSI);

bool is_persian_p_override_enabled = false;

static const key_override_t override_persian_p_in_non_standard_farsi_layout = {
    .trigger_mods           = 0,
    .layers                 = 1 << _FARSI,
    .suppressed_mods        = 0,
    .options                = ko_options_default,
    .negative_mod_mask      = 0,
    .custom_action          = NULL,
    .context                = NULL,
    .trigger                = KC_M,
    .replacement            = KC_BSLS,
    .enabled                = &is_persian_p_override_enabled
};

const key_override_t *key_overrides[] = {
    &override_swap_qoute_and_double_qoute, &override_shift_slash_is_back_slash, &override_swap_minus_and_underscore, &override_shift_dot_is_right_parenthesis, &override_shift_comma_is_left_parenthesis, &override_persian_shift_kaf_is_gaf, &override_persian_shift_he_is_che, &override_persian_shift_khe_is_jim,
    &override_persian_p_in_non_standard_farsi_layout
};