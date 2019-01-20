#ifndef VANIR_LOGGERCOLOR_H
#define VANIR_LOGGERCOLOR_H

#include <Vanir/LoggerColors.h>
#include <ostream>

// TODO: Add linux color support with ANSI

namespace Vanir
{
    class LoggerColor
    {
    public:
        explicit LoggerColor(LoggerColors foregroundColor = LoggerColors_White,
                             LoggerColors backgroundColor = LoggerColors_Black);

        friend std::ostream& operator<<(std::ostream& os, const LoggerColor& loggerColor);
        friend std::basic_ostream<wchar_t>& operator<<(std::basic_ostream<wchar_t>& os, const LoggerColor& loggerColor);

    private:
        LoggerColors m_foregroundColor;
        LoggerColors m_backgroundColor;
    };

} /* Namespace Vanir. */

#endif /* VANIR_LOGGERCOLOR_H. */
