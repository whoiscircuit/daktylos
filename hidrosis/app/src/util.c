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


int check_signal(sigset_t *set) {
    sigset_t pending;
    if (sigpending(&pending) == -1)
        return -1;

    for (int sig = 1; sig < NSIG; sig++) {
        if (sigismember(set, sig) && sigismember(&pending, sig)) {
            return sig;
        }
    }
    return 0;
}
