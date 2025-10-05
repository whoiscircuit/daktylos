#ifdef __linux__
#include <stdio.h>
#include <X11/XKBlib.h>
#include <X11/extensions/XKBrules.h>
#include <X11/extensions/XKBstr.h>
#include "layout.h"
#include "log.h"

static int x11_error_handler(Display *dpy, XErrorEvent *error) {
    char buf[256];
    XGetErrorText(dpy, error->error_code, buf, sizeof(buf));
    LOG_ERROR("X11 error: %s\n", buf);
    return 0; // continue execution
}


Display* g_display = NULL;
XkbDescRec *g_kbd = NULL;


int x11_init_keyboard_layout(){
    XSetErrorHandler(x11_error_handler);
    g_display = XOpenDisplay(NULL);
    if (!g_display) {
        LOG_ERROR("Failed to open X display\n");
        return -1;
    }
    g_kbd = XkbAllocKeyboard();
    if (!g_kbd) {
        XCloseDisplay(g_display);
        return -1;
    }
    return 0;
}


keyboard_layout_t x11_get_keyboard_layout() {
    int device_id = XkbUseCoreKbd;

    g_kbd->dpy = g_display;
    if (XkbGetNames(g_display, XkbGroupNamesMask, g_kbd) != Success) {
        return -1;
    }

    XkbStateRec state;
    if (XkbGetState(g_display, device_id, &state) != Success) {
        return -1;
    }

    char *layout = XGetAtomName(g_display, g_kbd->names->groups[state.group]);
    if (!layout) {
        return -1;
    }

    keyboard_layout_t result = get_layout_from_string(layout);

    XFree(layout);
    return result;
}

void x11_close_keyboard_layout(){
    XkbFreeKeyboard(g_kbd, 0, True);
    XCloseDisplay(g_display);
}

#endif
