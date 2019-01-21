#ifndef VANIR_LOGGERCOLORS_H
#define VANIR_LOGGERCOLORS_H

namespace Vanir
{
#ifdef PLATFORM_WINDOWS
    enum LoggerColors
    {
        LoggerColors_Black,
        LoggerColors_Blue,
        LoggerColors_Green,
        LoggerColors_Cyan,
        LoggerColors_Red,
        LoggerColors_Magenta,
        LoggerColors_Yellow,
        LoggerColors_White,
        LoggerColors_Gray,
        LoggerColors_Bright_Blue,
        LoggerColors_Bright_Green,
        LoggerColors_Bright_Cyan,
        LoggerColors_Bright_Red,
        LoggerColors_Bright_Magenta,
        LoggerColors_Bright_Yellow,
        LoggerColors_Bright_Gray,
        LoggerColors_Default = 20
    };
#else
    enum LoggerColors
    {
        LoggerColors_Black,
        LoggerColors_Red,
        LoggerColors_Green,
        LoggerColors_Yellow,
        LoggerColors_Blue,
        LoggerColors_Magenta,
        LoggerColors_Cyan,
        LoggerColors_Bright_Gray,
        LoggerColors_Gray = 10,
        LoggerColors_Bright_Red,
        LoggerColors_Bright_Green,
        LoggerColors_Bright_Yellow,
        LoggerColors_Bright_Blue,
        LoggerColors_Bright_Magenta,
        LoggerColors_Bright_Cyan,
        LoggerColors_Bright_White,
        LoggerColors_Default = 20
    };
#endif

} /* Namespace Vanir. */

#endif /* VANIR_LOGGERCOLORS_H. */
