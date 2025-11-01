#pragma once

typedef enum {
    LAYOUT_ENGLISH = 0,
    LAYOUT_FARSI = 1,
    LAYOUT_INTERNATIONAL = 2,
    LAYOUT_INTERNATIONAL_WITHOUT_DEAD_KEYS = 3,
    LAYOUT_FARSI_STANDARD = 4,
    LAYOUT_UNKNOWN = -1
} keyboard_layout_t;

keyboard_layout_t get_keyboard_layout();
keyboard_layout_t get_layout_from_string(char* str);
const char* layout_to_string(keyboard_layout_t layout);


#ifdef __linux__
keyboard_layout_t x11_get_keyboard_layout();
keyboard_layout_t hyprland_get_keyboard_layout();
#endif