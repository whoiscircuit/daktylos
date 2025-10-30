#include <ctype.h>
#include <string.h>
#include "layout.h"

static void tolowercase(char* str){
    char* letter = str;
    while(*letter != '\0'){
        *letter = tolower(*letter);
        letter += 1;
    }
}


int get_layout_from_string(char* str){
    tolowercase(str);
    if(strstr(str,"persian") || strstr(str,"farsi")){
        return LAYOUT_FARSI;
    }
    else if(strstr(str,"international") && strstr(str,"altgr")) {
        return LAYOUT_INTERNATIONAL_WITHOUT_DEAD_KEYS;
    }
    else if(strstr(str,"international")) {
        return LAYOUT_INTERNATIONAL;
    }
    else if(strstr(str,"english")) {
        return LAYOUT_ENGLISH;
    }
    else {
        return LAYOUT_UNKNOWN;
    }
}

const char* layout_to_string(keyboard_layout_t layout){
    switch(layout){
        case LAYOUT_ENGLISH:
            return "English";
        case LAYOUT_INTERNATIONAL:
            return "English International";
            break;
        case LAYOUT_INTERNATIONAL_WITHOUT_DEAD_KEYS:
            return "English International (without dead keys)";
            break;
        case LAYOUT_FARSI:
            return "Farsi";
        default:
            return "Unknown";
    }
}
