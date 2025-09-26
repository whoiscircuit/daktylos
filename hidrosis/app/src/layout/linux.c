#ifdef __linux__
#include <stdio.h>
#include <string.h>
#include <X11/XKBlib.h>
#include <X11/extensions/XKBrules.h>
#include <X11/extensions/XKBstr.h>
#include "layout.h"

int get_keyboard_layout(){
    Display *dpy = XOpenDisplay(NULL);
    if (!dpy) {
        fprintf(stderr, "Failed to open display\n");
        return -1;
    }

    int device_id = XkbUseCoreKbd;
    XkbDescRec *kbd = XkbAllocKeyboard();
    if (!kbd) {
        fprintf(stderr, "Failed to alloc keyboard\n");
        return -1;
    }

    kbd->dpy = dpy;
    if (XkbGetNames(dpy, XkbGroupNamesMask, kbd) != Success) {
        fprintf(stderr, "XkbGetNames failed\n");
        return -1;
    }

    XkbStateRec state;
    if (XkbGetState(dpy, device_id, &state) != Success) {
        fprintf(stderr, "XkbGetState failed\n");
        return -1;
    }

    char *layout = XGetAtomName(dpy, kbd->names->groups[state.group]);
    if (!layout) {
        printf("Failed to get the name of the active layout.");
        return -1;
    }

    int result = get_layout_id_from_string(layout);


    XFree(layout);

    XkbFreeKeyboard(kbd, 0, True);
    XCloseDisplay(dpy);
    return result;
}
#endif
