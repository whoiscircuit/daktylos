#pragma once
#include <stddef.h>
#include <stdbool.h>

/* Six levels */
typedef enum {
    LOG_LEVEL_TRACE = 0,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL,
} log_level_t;

/* Public API */
int         log_init(const char *ident);
void        log_shutdown(void);
void        log_set_level(log_level_t lvl);
log_level_t log_get_level(void);

void log_log(log_level_t lvl, const char *fmt, ...);

#define LOG_TRACE(...) log_log(LOG_LEVEL_TRACE, __VA_ARGS__)
#define LOG_DEBUG(...) log_log(LOG_LEVEL_DEBUG, __VA_ARGS__)
#define LOG_INFO(...) log_log(LOG_LEVEL_INFO, __VA_ARGS__)
#define LOG_WARN(...) log_log(LOG_LEVEL_WARN, __VA_ARGS__)
#define LOG_ERROR(...) log_log(LOG_LEVEL_ERROR, __VA_ARGS__)
#define LOG_FATAL(...) log_log(LOG_LEVEL_FATAL, __VA_ARGS__)

// enable/disable colors on stderr. default enabled when stderr is a tty.
void log_set_colors(bool on);

// platform specific functions
int  platform_log_init(const char *ident);
void platform_log_close(void);
void platform_log_write(log_level_t level, const char *msg);

int platform_is_stderr_tty(void);
int platform_enable_virtual_terminal(void);

void format_timestamp(char *buf, size_t buflen);
const char *get_log_level_name(log_level_t lvl);
