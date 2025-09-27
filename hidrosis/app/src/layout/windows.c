#ifdef _WIN32
#    include <windows.h>
#    include <stdio.h>
#    include "layout.h"
int get_keyboard_layout() {
    HKL hkl = GetKeyboardLayout(0);

    // Layout ID as string
    char name[KL_NAMELENGTH];
    if (!GetKeyboardLayoutNameA(name)) {
        return -1;
    }

    int result = get_layout_id_from_string(name);
    return result;
}
#endif
