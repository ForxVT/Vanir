#include "LoggerColor.h"
#ifdef PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

namespace Vanir
{
    LoggerColor::LoggerColor(LoggerColors foregroundColor, LoggerColors backgroundColor) :
            m_foregroundColor(foregroundColor), m_backgroundColor(backgroundColor)
    {

    }

    std::ostream &operator<<(std::ostream &os, const LoggerColor &loggerColor)
    {
#ifdef PLATFORM_WINDOWS
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdout, loggerColor.m_foregroundColor + loggerColor.m_backgroundColor);
#endif

        return os;
    }

    std::basic_ostream<wchar_t> &operator<<(std::basic_ostream<wchar_t> &os, const LoggerColor &loggerColor)
    {
#ifdef PLATFORM_WINDOWS
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdout, loggerColor.m_foregroundColor + loggerColor.m_backgroundColor);
#endif

        return os;
    }

} /* Namespace Vanir. */