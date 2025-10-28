#ifdef __unix__
#    include "log.h"
#    include <syslog.h>
#    include <stdlib.h>
#    include <string.h>
#    include <unistd.h>
#    include <stdio.h>

static char *g_ident = NULL;

int platform_is_stderr_tty(void) {
    return isatty(fileno(stderr));
}

int platform_enable_virtual_terminal(void) {
    return 1;
}

int platform_log_init(const char *ident) {
    g_ident = ident ? strdup(ident) : strdup("hidrosis-service");
    openlog(g_ident, LOG_PID | LOG_NDELAY, LOG_DAEMON);
    return 0;
}

void platform_log_close(void) {
    if (g_ident) {
        free(g_ident);
        g_ident = NULL;
    }
    closelog();
}

static int lvl_to_priority(log_level_t lvl) {
    switch (lvl) {
        case LOG_LEVEL_TRACE:
        case LOG_LEVEL_DEBUG:
            return LOG_DEBUG;
        case LOG_LEVEL_INFO:
            return LOG_INFO;
        case LOG_LEVEL_WARN:
            return LOG_WARNING;
        case LOG_LEVEL_ERROR:
            return LOG_ERR;
        case LOG_LEVEL_FATAL:
            return LOG_CRIT;
        default:
            return LOG_INFO;
    }
}

void platform_log_write(log_level_t level, const char *msg) {
    /* send to syslog only. stderr is handled by log.c */
    syslog(lvl_to_priority(level), "%s", msg);
}
#endif
