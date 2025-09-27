#ifdef __linux__
#    include <stdio.h>
#    include <string.h>
#    include <X11/XKBlib.h>
#    include <X11/extensions/XKBrules.h>
#    include <X11/extensions/XKBstr.h>
#    include "layout.h"

int get_keyboard_layout() {
    Display *dpy = XOpenDisplay(NULL);
    if (!dpy) {
        return -1;
    }

    int         device_id = XkbUseCoreKbd;
    XkbDescRec *kbd       = XkbAllocKeyboard();
    if (!kbd) {
        return -1;
    }

    kbd->dpy = dpy;
    if (XkbGetNames(dpy, XkbGroupNamesMask, kbd) != Success) {
        return -1;
    }

    XkbStateRec state;
    if (XkbGetState(dpy, device_id, &state) != Success) {
        return -1;
    }

    char *layout = XGetAtomName(dpy, kbd->names->groups[state.group]);
    if (!layout) {
        return -1;
    }

    keyboard_layout_t result = get_layout_from_string(layout);

    XFree(layout);

    XkbFreeKeyboard(kbd, 0, True);
    XCloseDisplay(dpy);
    return result;
}
#endif
