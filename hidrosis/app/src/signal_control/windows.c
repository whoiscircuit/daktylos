#ifdef _WIN32
#include <windows.h>
#include <stdbool.h>

static volatile bool g_interrupted = false;

BOOL WINAPI ConsoleHandler(DWORD ctrlType)
{
    switch (ctrlType)
    {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
        g_interrupted = true;
        return TRUE;
    default:
        return FALSE;
    }
}

void signal_init()
{
    SetConsoleCtrlHandler(ConsoleHandler, TRUE);
}

int check_signal()
{
    return g_interrupted ? 1 : 0;
}
#endif