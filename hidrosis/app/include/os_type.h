#pragma once

typedef enum {
    OS_TYPE_UNKNOWN = 0x00,
    OS_TYPE_WINDOWS = 0x01,
    OS_TYPE_MACOS   = 0x02,
    OS_TYPE_LINUX   = 0x03
} os_type_t;

os_type_t get_os_type();
const char* os_type_to_string(os_type_t os);
