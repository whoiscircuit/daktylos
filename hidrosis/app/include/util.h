#pragma once
#include <signal.h>
void sleep_for_ms(unsigned int ms);
int check_signal(sigset_t *set);
