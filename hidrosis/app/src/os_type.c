#include "os_type.h"

os_type_t get_os_type(){
#ifdef _WIN32
    return OS_TYPE_WINDOWS;
#elif __APPLE__
    return OS_TYPE_MACOS;
#elif __linux__
    return OS_TYPE_LINUX;
#else
    return OS_TYPE_UNKNOWN;
#endif
}

const char* os_type_to_string(os_type_t os){
    switch(os){
        case OS_TYPE_WINDOWS:
            return "Windows";
        case OS_TYPE_MACOS:
            return "macOS";
        case OS_TYPE_LINUX:
            return "Linux";
        default:
            return "Unknown";
    }
}
