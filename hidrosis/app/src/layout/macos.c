#ifdef __APPLE__
#    include <Carbon/Carbon.h>
#    include <stdio.h>
#    include "layout.h"
#include "util.h"
int get_keyboard_layout() {
    TISInputSourceRef source = TISCopyCurrentKeyboardInputSource();
    if (!source) {
        return -1;
    }

    // Get layout ID or name
    CFStringRef layoutName = TISGetInputSourceProperty(source, kTISPropertyLocalizedName);
    if (!layoutName) {
        return -1;
    }
    char name[128];
    if (!CFStringGetCString(layoutName, name, sizeof(name), kCFStringEncodingUTF8)) {
        return -1;
    }
    int result = get_layout_from_string(name);

    CFRelease(source);

    return result;
}
#endif
