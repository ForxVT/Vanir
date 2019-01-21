#ifndef VANIR_LOGGERCOLOR_H
#define VANIR_LOGGERCOLOR_H

#include <Vanir/LoggerColors.h>
#include <ostream>

namespace Vanir
{
    class LoggerColor
    {
    public:
#ifdef PLATFORM_WINDOWS
        explicit LoggerColor(LoggerColors foregroundColor = LoggerColors_Default,
                             LoggerColors backgroundColor = LoggerColors_Default);
#else
        explicit LoggerColor(LoggerColors foregroundColor = LoggerColors_Default,
                             LoggerColors backgroundColor = LoggerColors_Default);
#endif

        friend std::ostream& operator<<(std::ostream& os, const LoggerColor& loggerColor);
        friend std::basic_ostream<wchar_t>& operator<<(std::basic_ostream<wchar_t>& os, const LoggerColor& loggerColor);

    private:
        LoggerColors m_foregroundColor;
        LoggerColors m_backgroundColor;
    };

} /* Namespace Vanir. */

#endif /* VANIR_LOGGERCOLOR_H. */
