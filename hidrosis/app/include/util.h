#pragma once
#include <signal.h>
void sleep_for_seconds(unsigned int seconds);
int check_signal(sigset_t *set);
