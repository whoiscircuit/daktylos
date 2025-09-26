#include <ctype.h>
#ifdef __linux__
#include <stdio.h>
#include <string.h>
#include <X11/XKBlib.h>
#include <X11/extensions/XKBrules.h>
#include <X11/extensions/XKBstr.h>
#include "layout.h"

static void tolowercase(char* str){
    char* letter = str;
    while(*letter != '\0'){
        *letter = tolower(*letter);
        letter += 1;
    }
}

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

    int result;
    tolowercase(layout);
    if(strstr(layout,"persian") || strstr(layout,"farsi")){
        printf("Active keyboard layout is Farsi.\n");
        result = LAYOUT_FARSI;
    }
    else {
        printf("Active keyboard layout is English.\n");
        result = LAYOUT_ENGLISH;
    }


    XFree(layout);

    XkbFreeKeyboard(kbd, 0, True);
    XCloseDisplay(dpy);
    return result;
}
#endif
