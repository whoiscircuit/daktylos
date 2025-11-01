#ifdef __linux__
#include <stdio.h>
#include <X11/XKBlib.h>
#include <X11/extensions/XKBrules.h>
#include <X11/extensions/XKBstr.h>
#include "layout.h"
#include "log.h"
#include "util.h"

static int x11_error_handler(Display *dpy, XErrorEvent *error) {
    char buf[256];
    XGetErrorText(dpy, error->error_code, buf, sizeof(buf));
    LOG_ERROR("X11 error: %s\n", buf);
    return 0; // continue execution
}


Display* g_display = NULL;
XkbDescRec *g_kbd = NULL;


keyboard_layout_t x11_get_keyboard_layout() {

    XSetErrorHandler(x11_error_handler);
    if(!g_display){
        g_display = XOpenDisplay(NULL);
        if (!g_display) {
            LOG_ERROR("Failed to open X display\n");
            return LAYOUT_UNKNOWN;
        }
    }
    if(!g_kbd){
        g_kbd = XkbAllocKeyboard();
        if (!g_kbd) {
            XCloseDisplay(g_display);
            return LAYOUT_UNKNOWN;
        }
    }
    int device_id = XkbUseCoreKbd;

    g_kbd->dpy = g_display;
    if (XkbGetNames(g_display, XkbGroupNamesMask, g_kbd) != Success) {
        return LAYOUT_UNKNOWN;
    }

    XkbStateRec state;
    if (XkbGetState(g_display, device_id, &state) != Success) {
        return LAYOUT_UNKNOWN;
    }

    char *layout = XGetAtomName(g_display, g_kbd->names->groups[state.group]);
    if (!layout) {
        return LAYOUT_UNKNOWN;
    }

    keyboard_layout_t result = get_layout_from_string(layout);

    XFree(layout);
    return result;
}

#endif
