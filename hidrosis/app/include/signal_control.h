#pragma once
#include <bits/types/sigset_t.h>

extern sigset_t set;
extern int sig;

void signal_init();
int  check_signal(sigset_t *set);