#include "log.h"
#include <time.h>
#include <stdio.h>
#include <string.h>

void format_timestamp(char *buf, size_t buflen) {
    time_t     t = time(NULL);
    struct tm  tm_buf;
    struct tm *tm_ptr = gmtime(&t);
    if (!tm_ptr) {
        if (buflen > 0) buf[0] = '\0';
        return;
    }
    tm_buf = *tm_ptr;
    strftime(buf, buflen, "%Y-%m-%dT%H:%M:%SZ", &tm_buf);
}

const char *get_log_level_name(log_level_t lvl) {
    switch (lvl) {
        case LOG_LEVEL_TRACE:
            return "TRACE";
        case LOG_LEVEL_DEBUG:
            return "DEBUG";
        case LOG_LEVEL_INFO:
            return "INFO";
        case LOG_LEVEL_WARN:
            return "WARN";
        case LOG_LEVEL_ERROR:
            return "ERROR";
        case LOG_LEVEL_FATAL:
            return "FATAL";
        default:
            return "UNK";
    }
}
