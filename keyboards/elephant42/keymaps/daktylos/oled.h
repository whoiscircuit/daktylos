
typedef enum {
    OLED_OFF,
    OLED_MENU,
    OLED_PREFS,
    OLED_JOYSTICK,
    OLED_BOOTLOADER,

    NUMBER_OF_OLED_MODES
} OLED_MODE;

typedef enum {
    MENU_JOYSTICK,
    MENU_PREFS,
    MENU_FLASH,

    NUMBER_OF_MENU_ITEMS,
} MENU_ITEM;

typedef enum {
    PREF_TAP_TERM,

    NUMBER_OF_PREFS_ITEMS,
} PREFS_ITEM;

typedef union {
    uint8_t raw;
    struct {
        OLED_MODE  mode : 3;
        MENU_ITEM  menu_item : 2;
        PREFS_ITEM prefs_index : 2;
    };
} oled_state_t;

extern oled_state_t oled_state;
