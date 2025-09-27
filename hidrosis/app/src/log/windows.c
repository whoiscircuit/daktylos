#ifdef _WIN32
#    include "log.h"
#    include <windows.h>
#    include <stdio.h>
#    include <string.h>
#    include <io.h>
#    include <fcntl.h>

static HANDLE g_event_source = NULL;
static char  *g_ident        = NULL;

int platform_is_stderr_tty(void) {
    return _isatty(_fileno(stderr));
}

int platform_enable_virtual_terminal(void) {
    HANDLE hOut = GetStdHandle(STD_ERROR_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return 0;

    DWORD mode = 0;
    if (!GetConsoleMode(hOut, &mode)) return 0;

    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, mode)) return 0;
    return 1;
}

int platform_log_init(const char *ident) {
    g_ident        = ident ? _strdup(ident) : _strdup("service");
    g_event_source = RegisterEventSourceA(NULL, g_ident);
    return 0;
}

void platform_log_close(void) {
    if (g_event_source) {
        DeregisterEventSource(g_event_source);
        g_event_source = NULL;
    }
    if (g_ident) {
        free(g_ident);
        g_ident = NULL;
    }
}

static WORD lvl_to_event_type(log_level_t lvl) {
    switch (lvl) {
        case LOG_LEVEL_TRACE:
        case LOG_LEVEL_DEBUG:
            return EVENTLOG_INFORMATION_TYPE;
        case LOG_LEVEL_INFO:
            return EVENTLOG_INFORMATION_TYPE;
        case LOG_LEVEL_WARN:
            return EVENTLOG_WARNING_TYPE;
        case LOG_LEVEL_ERROR:
            return EVENTLOG_ERROR_TYPE;
        case LOG_LEVEL_FATAL:
            return EVENTLOG_ERROR_TYPE;
        default:
            return EVENTLOG_INFORMATION_TYPE;
    }
}

void platform_log_write(log_level_t level, const char *msg) {
    if (!g_event_source) return;
    LPCSTR strings[1];
    strings[0] = msg;
    ReportEventA(g_event_source, lvl_to_event_type(level), 0, 0, NULL, 1, 0, strings, NULL);
}
#endif
