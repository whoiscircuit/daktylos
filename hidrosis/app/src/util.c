#include "util.h"
#ifdef _WIN32
#    include <windows.h>
#else
#    include <unistd.h>
#endif

void sleep_for_seconds(unsigned int seconds) {
#ifdef _WIN32
    Sleep(seconds * 1000);
#else
    sleep(seconds);
#endif
}
