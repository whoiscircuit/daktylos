#ifdef __linux__
#include <wayland-client.h>
#include <xkbcommon/xkbcommon.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include "layout.h"

int wayland_init_keyboard_layout(){
    return 0;
}

keyboard_layout_t wayland_get_keyboard_layout(){
    return LAYOUT_ENGLISH;
}
void wayland_close_keyboard_layout(){
    
}
#endif