#include <stdlib.h>
#include "layout.h"

int init_keyboard_layout(void) {
    const char *val = getenv("WAYLAND_DISPLAY");
    if (val) {
        return wayland_init_keyboard_layout();
    } else {
        return x11_init_keyboard_layout();
    }
}
void close_keyboard_layout(void) {
    const char *val = getenv("WAYLAND_DISPLAY");
    if (val) {
        wayland_close_keyboard_layout();
    } else {
        x11_close_keyboard_layout();
    }
}
keyboard_layout_t get_keyboard_layout(void) {
    const char *val = getenv("WAYLAND_DISPLAY");
    if (val) {
        return wayland_get_keyboard_layout();
    } else {
        return x11_get_keyboard_layout();
    }
}