#include "signal_control.h"
#include <signal.h>

sigset_t set;
int sig;

void signal_init(){
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTERM);
    pthread_sigmask(SIG_BLOCK, &set, 0);
}

int check_signal(sigset_t *set) {
    sigset_t pending;
    if (sigpending(&pending) == -1) return -1;

    for (int sig = 1; sig < NSIG; sig++) {
        if (sigismember(set, sig) && sigismember(&pending, sig)) {
            return sig;
        }
    }
    return 0;
}