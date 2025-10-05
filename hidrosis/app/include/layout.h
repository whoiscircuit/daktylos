#pragma once

typedef enum {
    LAYOUT_ENGLISH = 0,
    LAYOUT_FARSI = 1,
    LAYOUT_UNKNOWN = -1
} keyboard_layout_t;

int init_keyboard_layout();
keyboard_layout_t get_keyboard_layout();
keyboard_layout_t get_layout_from_string(char* str);
void close_keyboard_layout();
const char* layout_to_string(keyboard_layout_t layout);


#ifdef __linux__
keyboard_layout_t x11_get_keyboard_layout();
keyboard_layout_t wayland_get_keyboard_layout();
int x11_init_keyboard_layout();
int wayland_init_keyboard_layout();
void x11_close_keyboard_layout();
void wayland_close_keyboard_layout();
#endif