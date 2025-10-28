#ifdef _WIN32
#    include <windows.h>
#    include <stdio.h>
#    include "layout.h"
#include "util.h"

int init_keyboard_layout(){
    return 0;
}

void close_keyboard_layout(){
    
}

int get_keyboard_layout() {
    HWND fg = GetForegroundWindow();
    DWORD threadId = GetWindowThreadProcessId(fg, NULL);
    HKL hkl = GetKeyboardLayout(threadId);
    UINT_PTR hkl_val = (UINT_PTR)hkl;
    WORD langid = LOWORD((DWORD)hkl_val);
    LCID lcid = MAKELCID(langid, SORT_DEFAULT);
    char langName[128] = {0};
    if (GetLocaleInfoA(lcid, LOCALE_SLANGUAGE, langName, (int)sizeof(langName))){
        return get_layout_from_string(langName);
    }
    return LAYOUT_UNKNOWN;
}
#endif
