#include QMK_KEYBOARD_H
typedef enum {
    OS_UNKNOWN = 0,
    OS_WINDOWS = 1,
    OS_MACOS   = 2,
    OS_LINUX   = 3,
} OS_TYPE;

typedef enum {
    LAYOUT_ENGLISH                         = 0,
    LAYOUT_FARSI                           = 1,
    LAYOUT_INTERNATIONAL                   = 2,
    LAYOUT_INTERNATIONAL_WITHOUT_DEAD_KEYS = 3,
    LAYOUT_FARSI_NON_STANDARD              = 4,
} KEYBOARD_LAYOUT;

typedef union {
    uint8_t raw;
    struct {
        OS_TYPE         os_type : 2;
        KEYBOARD_LAYOUT active_layout : 3;
    };
} hid_state_t;

extern hid_state_t hid_state;