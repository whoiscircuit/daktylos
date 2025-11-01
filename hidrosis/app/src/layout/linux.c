#ifdef __unix__
#include <stdlib.h>
#include "layout.h"

keyboard_layout_t get_keyboard_layout(void) {
    const char *val = getenv("WAYLAND_DISPLAY");
    if (val) {
        return wayland_get_keyboard_layout();
    } else {
        return x11_get_keyboard_layout();
    }
}
#endif