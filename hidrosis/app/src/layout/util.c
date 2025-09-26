#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "layout.h"

static void tolowercase(char* str){
    char* letter = str;
    while(*letter != '\0'){
        *letter = tolower(*letter);
        letter += 1;
    }
}

int get_layout_id_from_string(char* str){
    tolowercase(str);
    if(strstr(str,"persian") || strstr(str,"farsi")){
        printf("Active keyboard layout is Farsi.\n");
        return LAYOUT_FARSI;
    }
    else {
        printf("Active keyboard layout is English.\n");
        return LAYOUT_ENGLISH;
    }
}
