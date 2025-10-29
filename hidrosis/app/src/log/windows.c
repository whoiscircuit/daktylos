#ifdef _WIN32
#    include "log.h"
#    include <windows.h>
#    include <stdio.h>
#    include <string.h>
#    include <io.h>
#    include <fcntl.h>

static HANDLE g_event_source = NULL;
static char  *g_ident        = NULL;
static FILE  *g_log_file     = NULL;

// Get the directory of the executable
static void get_executable_path(char *buffer, size_t size) {
    DWORD length = GetModuleFileNameA(NULL, buffer, (DWORD)size);
    if (length == 0 || length == size) {
        buffer[0] = '\0';
        return;
    }
    // Remove the executable name to leave only the directory
    for (int i = length - 1; i >= 0; --i) {
        if (buffer[i] == '\\' || buffer[i] == '/') {
            buffer[i + 1] = '\0';
            break;
        }
    }
}

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
    g_ident = ident ? _strdup(ident) : _strdup("Hidrosis_Service");
    g_event_source = RegisterEventSourceA(NULL, g_ident);

    // Open log file in the executable directory
    char exe_path[MAX_PATH];
    get_executable_path(exe_path, sizeof(exe_path));
    strncat(exe_path, "hidrosis.log", sizeof(exe_path) - strlen(exe_path) - 1);

    g_log_file = fopen(exe_path, "a");
    if (!g_log_file) {
        fprintf(stderr, "Failed to open log file: %s\n", exe_path);
    }

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
    if (g_log_file) {
        fclose(g_log_file);
        g_log_file = NULL;
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
        case LOG_LEVEL_FATAL:
            return EVENTLOG_ERROR_TYPE;
        default:
            return EVENTLOG_INFORMATION_TYPE;
    }
}

static const char* lvl_to_string(log_level_t lvl) {
    switch (lvl) {
        case LOG_LEVEL_TRACE: return "TRACE";
        case LOG_LEVEL_DEBUG: return "DEBUG";
        case LOG_LEVEL_INFO:  return "INFO";
        case LOG_LEVEL_WARN:  return "WARN";
        case LOG_LEVEL_ERROR: return "ERROR";
        case LOG_LEVEL_FATAL: return "FATAL";
        default:              return "INFO";
    }
}

void platform_log_write(log_level_t level, const char *msg) {
    // Write to Windows Event Log
    if (g_event_source) {
        LPCSTR strings[1];
        strings[0] = msg;
        ReportEventA(g_event_source, lvl_to_event_type(level), 0, 0, NULL, 1, 0, strings, NULL);
    }

    // Write to file
    if (g_log_file) {
        SYSTEMTIME st;
        GetLocalTime(&st);
        fprintf(g_log_file, "[%04d-%02d-%02d %02d:%02d:%02d] [%s] %s\n",
                st.wYear, st.wMonth, st.wDay,
                st.wHour, st.wMinute, st.wSecond,
                lvl_to_string(level), msg);
        fflush(g_log_file);
    }
}
#endif
