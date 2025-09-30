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

int get_keyboard_layout() {
    Display *dpy = XOpenDisplay(NULL);
    if (!dpy) {
        LOG_ERROR("Failed to open X display\n");
        return -1;
    }

    XErrorHandler old_handler = XSetErrorHandler(x11_error_handler);

    int device_id = XkbUseCoreKbd;
    XkbDescRec *kbd = XkbAllocKeyboard();
    if (!kbd) {
        XCloseDisplay(dpy);
        XSetErrorHandler(old_handler);
        return -1;
    }

    kbd->dpy = dpy;
    if (XkbGetNames(dpy, XkbGroupNamesMask, kbd) != Success) {
        XkbFreeKeyboard(kbd, 0, True);
        XCloseDisplay(dpy);
        XSetErrorHandler(old_handler);
        return -1;
    }

    XkbStateRec state;
    if (XkbGetState(dpy, device_id, &state) != Success) {
        XkbFreeKeyboard(kbd, 0, True);
        XCloseDisplay(dpy);
        XSetErrorHandler(old_handler);
        return -1;
    }

    char *layout = XGetAtomName(dpy, kbd->names->groups[state.group]);
    if (!layout) {
        XkbFreeKeyboard(kbd, 0, True);
        XCloseDisplay(dpy);
        XSetErrorHandler(old_handler);
        return -1;
    }

    keyboard_layout_t result = get_layout_from_string(layout);

    XFree(layout);
    XkbFreeKeyboard(kbd, 0, True);
    XCloseDisplay(dpy);
    XSetErrorHandler(old_handler);

    return result;
}
#endif
