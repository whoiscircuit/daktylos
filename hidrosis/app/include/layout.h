#pragma once

enum KEYBOARD_LAYOUT {
    LAYOUT_ENGLISH = 0,
    LAYOUT_FARSI = 1,
};

int get_keyboard_layout();
int get_layout_id_from_string(char* str);
