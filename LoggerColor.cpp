#include <Vanir/LoggerColor.h>
#include <Vanir/Logger.h>
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
        if (!Logger::IsWritingToFile())
        {
#ifdef PLATFORM_WINDOWS
            HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

            int foregroundColor = 15;
            int backgroundColor = 0;

            if (loggerColor.m_foregroundColor != 20)
                foregroundColor = loggerColor.m_foregroundColor;

            if (loggerColor.m_backgroundColor != 20)
                backgroundColor = loggerColor.m_backgroundColor;

            SetConsoleTextAttribute(hStdout, foregroundColor + backgroundColor);

            return os;
#else
            int foregroundColor = 39;
            int backgroundColor = 49;

            if (loggerColor.m_foregroundColor < 10)
                foregroundColor = loggerColor.m_foregroundColor + 30;
            else if (loggerColor.m_foregroundColor != 20)
                foregroundColor = loggerColor.m_foregroundColor + 80;

            if (loggerColor.m_backgroundColor < 10)
                backgroundColor = loggerColor.m_backgroundColor + 40;
            else if (loggerColor.m_backgroundColor != 20)
                backgroundColor = loggerColor.m_backgroundColor + 90;

            return os << "\u001b[0;" + std::to_string(foregroundColor) + ";" + std::to_string(backgroundColor) + "m";
#endif
        }
        else
        {
            return os;
        }
    }

    std::basic_ostream<wchar_t> &operator<<(std::basic_ostream<wchar_t> &os, const LoggerColor &loggerColor)
    {
        if (!Logger::IsWritingToFile())
        {
#ifdef PLATFORM_WINDOWS
            HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hStdout, loggerColor.m_foregroundColor + loggerColor.m_backgroundColor);

            int foregroundColor = 15;
            int backgroundColor = 0;

            if (loggerColor.m_foregroundColor != 20)
                foregroundColor = loggerColor.m_foregroundColor;

            if (loggerColor.m_backgroundColor != 20)
                backgroundColor = loggerColor.m_backgroundColor;

            SetConsoleTextAttribute(hStdout, foregroundColor + backgroundColor);

            return os;
#endif
        }
        else
        {
            return os;
        }
    }

} /* Namespace Vanir. */