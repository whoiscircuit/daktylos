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


#include <windows.h>
#include <stdio.h>

int get_keyboard_layout() {
    HWND fg = GetForegroundWindow();
    DWORD threadId = GetWindowThreadProcessId(fg, NULL);
    HKL hkl = GetKeyboardLayout(threadId);
    ActivateKeyboardLayout(hkl, KLF_SETFORPROCESS);
    // Extract language ID (low word) and KLID (high word)
    LANGID langid = LOWORD((DWORD_PTR)hkl);
    LCID lcid = MAKELCID(langid, SORT_DEFAULT);

    // Get language name
    char langName[128] = {0};
    if (!GetLocaleInfoA(lcid, LOCALE_SLANGUAGE, langName, sizeof(langName))) {
        return LAYOUT_UNKNOWN;
    }

    // Get keyboard layout name (KLID) like "00000409"
    char klName[KL_NAMELENGTH];
    if (GetKeyboardLayoutNameA(klName)) {
        // Open registry key for layout description
        HKEY hKey;
        char regPath[256];
        snprintf(regPath, sizeof(regPath), "SYSTEM\\CurrentControlSet\\Control\\Keyboard Layouts\\%s", klName);
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, regPath, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
            char layoutText[256] = {0};
            DWORD size = sizeof(layoutText);
            if (RegQueryValueExA(hKey, "Layout Text", NULL, NULL, (LPBYTE)layoutText, &size) == ERROR_SUCCESS) {
                // Append layout variant to language name
                strncat(langName, " ", sizeof(langName) - strlen(langName) - 1);
                strncat(langName, layoutText, sizeof(langName) - strlen(langName) - 1);
            }
            RegCloseKey(hKey);
        }
    }

    printf("Layout: %s\n", langName);
    return get_layout_from_string(langName);
}
#endif