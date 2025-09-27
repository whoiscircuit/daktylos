#ifdef __APPLE__
#    include <Carbon/Carbon.h>
#    include <stdio.h>
#    include "layout.h"
int get_keyboard_layout() {
    TISInputSourceRef source = TISCopyCurrentKeyboardInputSource();
    if (!source) {
        printf("Failed to get keyboard source\n");
        return -1;
    }

    // Get layout ID or name
    CFStringRef layoutName = TISGetInputSourceProperty(source, kTISPropertyLocalizedName);
    if (!layoutName) {
        printf("Failed to get the layout name!\n");
        return -1;
    }
    char name[128];
    if (!CFStringGetCString(layoutName, name, sizeof(name), kCFStringEncodingUTF8)) {
        printf("Failed to get the layout name!\n");
        return -1;
    }
    int result = get_layout_id_from_string(name);

    CFRelease(source);

    return result;
}
#endif
