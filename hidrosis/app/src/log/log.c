#include "log.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static log_level_t g_level     = LOG_LEVEL_INFO;
static char        g_ident[64] = "hidrosis-service";
static int         g_colors    = -1; // -1 = auto-detect, 0 = off, 1 = on

static const char *level_color(log_level_t lvl) {
    switch (lvl) {
        case LOG_LEVEL_TRACE:
            return "\x1b[90m"; // gray
        case LOG_LEVEL_DEBUG:
            return "\x1b[36m"; // cyan
        case LOG_LEVEL_INFO:
            return "\x1b[32m"; // green
        case LOG_LEVEL_WARN:
            return "\x1b[33m"; // yellow
        case LOG_LEVEL_ERROR:
            return "\x1b[31m"; // red
        case LOG_LEVEL_FATAL:
            return "\x1b[35m"; // magenta
        default:
            return "";
    }
}

void log_set_colors(bool on) {
    g_colors = on ? 1 : 0;
    if (g_colors == 1) {
        platform_enable_virtual_terminal();
    }
}

int log_init(const char *ident) {
    if (ident) {
        strncpy(g_ident, ident, sizeof(g_ident) - 1);
        g_ident[sizeof(g_ident) - 1] = '\0';
    }

    if (g_colors == -1) {
        g_colors = platform_is_stderr_tty() ? 1 : 0;
        if (g_colors == 1) platform_enable_virtual_terminal();
    }

    return platform_log_init(g_ident);
}

void log_shutdown(void) {
    platform_log_close();
}

void log_set_level(log_level_t lvl) {
    g_level = lvl;
}

log_level_t log_get_level(void) {
    return g_level;
}

void log_log(log_level_t lvl, const char *fmt, ...) {
    if (lvl < g_level) return;

    char ts[32];
    format_timestamp(ts, sizeof(ts));

    char    user_msg[1024];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(user_msg, sizeof(user_msg), fmt, ap);
    va_end(ap);

    // plain message for platform backends (no color)
    char plain[1400];
    snprintf(plain, sizeof(plain), "%s [%s]: %s", ts, get_log_level_name(lvl), user_msg);

    // colored message for stderr output (if enabled)
    if (g_colors) {
        const char *col   = level_color(lvl);
        const char *reset = "\x1b[0m";
        fprintf(stderr, "%s%s%s\n", col, plain, reset);
    } else {
        fprintf(stderr, "%s\n", plain);
    }
    fflush(stderr);

    platform_log_write(lvl, plain);
}
