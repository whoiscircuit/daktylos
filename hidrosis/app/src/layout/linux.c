#ifdef __unix__
#include <stdlib.h>
#include "layout.h"
#include <string.h>
#include "log.h"

keyboard_layout_t get_keyboard_layout(void) {
    const char *val = getenv("WAYLAND_DISPLAY");
    if (val) {
        const char *compositor = getenv("XDG_CURRENT_DESKTOP");
        if (compositor && strcmp(compositor, "Hyprland") == 0) {
            return hyprland_get_keyboard_layout();
        }
        else {
            LOG_ERROR("Unsupported compositor: %s", compositor);
            return LAYOUT_UNKNOWN;
        }
    } else {
        return x11_get_keyboard_layout();
    }
}
#endif