//==================================================================================//
//                                                                                  //
//  Copyright (c) 2019 Hugo Kindel <kindelhugo.pro@gmail.com>                       //
//                                                                                  //
//  This file is part of the Vanir project.                                         //
//  Licensed under MIT License:                                                     //
//                                                                                  //
//  Permission is hereby granted, free of charge, to any person obtaining           //
//  a copy of this software and associated documentation files (the "Software"),    //
//  to deal in the Software without restriction, including without limitation       //
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,        //
//  and/or sell copies of the Software, and to permit persons to whom the           //
//  Software is furnished to do so, subject to the following conditions:            //
//                                                                                  //
//  The above copyright notice and this permission notice shall be included in      //
//  all copies or substantial portions of the Software.                             //
//                                                                                  //
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      //
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        //
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     //
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          //
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   //
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   //
//  SOFTWARE.                                                                       //
//                                                                                  //
//==================================================================================//

#ifndef VANIR_LOGGER_LOGGER_H
#define VANIR_LOGGER_LOGGER_H

#include <fstream>
#include <iostream>
#ifdef _WIN32
#include <fcntl.h>
#include <codecvt>
#include <combaseapi.h>
#include <locale>
#include <codecvt>
#include <sstream>
#include <iomanip>
#include <algorithm>
#endif
#include <Vanir/Common.h>
#include <Vanir/Logger/LogColor.h>
#include <Vanir/String/String.h>

namespace Vanir {
    class Logger {
    public:
        static void Start(const std::string& filepath = "logs.log");
        static void StartNoLog();
        static void Stop();
        static void ResetCounters();
        static std::string LogHeader(const std::string& message, const std::string& function = std::string(), int line = -1);
        template <typename... Args>
        static void Log(Args&&... args) {
            m_writingToFile = true;

            if (m_fileOpened)
                ((m_file << std::forward<Args>(args)), ...) << std::endl;

            m_writingToFile = false;

            ((std::cout << std::forward<Args>(args)), ...) << LogColor() << std::endl;
        }
        static bool IsWritingToFile();
#ifdef _WIN32
        template <class T>
        static std::basic_ostream<wchar_t>& ULogConverter(T&& arg) {
            return std::wcout << arg;
        }
        static std::basic_ostream<wchar_t>& ULogConverter(std::string arg) {
            return std::wcout << ::Vanir::String::StringToWString(arg);
        }
        static std::basic_ostream<wchar_t>& ULogConverter(const char* arg) {
            return std::wcout << ::Vanir::String::StringToWString(arg);
        }
        template <typename... Args>
        static void ULog(Args&&... args) {
            m_writingToFile = true;

            if (m_fileOpened)
                ((m_file << std::forward<Args>(args)), ...) << std::endl;

            m_writingToFile = false;

            _setmode(_fileno(stdout), _O_WTEXT);
            ((ULogConverter(std::forward<Args>(args))), ...) << LogColor() << std::endl;
            _setmode(_fileno(stdout), _O_TEXT);
        }
#endif

        static int ErrorCount;
        static int WarningCount;
        static int InfoCount;

    private:
        static std::ofstream m_file;
        static bool m_writingToFile;
        static bool m_fileOpened;
        static bool m_log;
        static time_t m_time;
    };

} /* Namespace Vanir. */

/* Utility macro to reset logger counters. */
#define LOG_RESETCOUNTERS() ::Vanir::Logger::ResetCounters();

/* Logs utility macros. */
#define LOG(...) ::Vanir::Logger::Log(__VA_ARGS__);
#if defined(_DEBUG)
#define LOG_INFO(...) \ { \
    ::Vanir::Logger::Log(::Vanir::LogColor(::Vanir::TerminalColor_Bright_Blue), ::Vanir::Logger::LogHeader("INFO", __PRETTY_FUNCTION__, __LINE__), ::Vanir::LogColor(), __VA_ARGS__); \
    ::Vanir::Logger::InfoCount += 1; \
}
#define LOG_VERBOSE(...) \ { \
    ::Vanir::Logger::Log(::Vanir::LogColor(::Vanir::TerminalColor_Bright_Blue), ::Vanir::Logger::LogHeader("VERBOSE", __PRETTY_FUNCTION__, __LINE__), ::Vanir::LogColor(), __VA_ARGS__); \
    ::Vanir::Logger::WarningCount += 1; \
}
#define LOG_WARNING(...) \ { \
    ::Vanir::Logger::Log(::Vanir::LogColor(::Vanir::TerminalColor_Yellow), ::Vanir::Logger::LogHeader("WARNING", __PRETTY_FUNCTION__, __LINE__), ::Vanir::LogColor(), __VA_ARGS__); \
    ::Vanir::Logger::WarningCount += 1; \
}
#define LOG_ERROR(...) \ { \
    ::Vanir::Logger::Log(::Vanir::LogColor(::Vanir::TerminalColor_Red), ::Vanir::Logger::LogHeader("ERROR", __PRETTY_FUNCTION__, __LINE__), ::Vanir::LogColor(), __VA_ARGS__); \
    ::Vanir::Logger::ErrorCount += 1; \
}
#else
#define LOG_INFO(...) { \
    ::Vanir::Logger::Log(::Vanir::LogColor(::Vanir::TerminalColor_Bright_Blue), ::Vanir::Logger::LogHeader("INFO"), ::Vanir::LogColor(), __VA_ARGS__); \
    ::Vanir::Logger::InfoCount += 1; \
}
#define LOG_VERBOSE(...) { \
    ::Vanir::Logger::Log(::Vanir::LogColor(::Vanir::TerminalColor_Bright_Blue), ::Vanir::Logger::LogHeader("VERBOSE"), ::Vanir::LogColor(), __VA_ARGS__); \
    ::Vanir::Logger::WarningCount += 1; \
}
#define LOG_WARNING(...) { \
    ::Vanir::Logger::Log(::Vanir::LogColor(::Vanir::TerminalColor_Yellow), ::Vanir::Logger::LogHeader("WARNING"), ::Vanir::LogColor(), __VA_ARGS__); \
    ::Vanir::Logger::WarningCount += 1; \
}
#define LOG_ERROR(...) { \
    ::Vanir::Logger::Log(::Vanir::LogColor(::Vanir::TerminalColor_Red), ::Vanir::Logger::LogHeader("ERROR"), ::Vanir::LogColor(), __VA_ARGS__); \
    ::Vanir::Logger::ErrorCount += 1; \
}
#endif

/* Unicode logs utility macros. */
#ifdef _WIN32
#define ULOG(...) ::Vanir::Logger::ULog(__VA_ARGS__);
#if defined(_DEBUG)
#define ULOG_INFO(...) { \
    ::Vanir::Logger::ULog(::Vanir::LogColor(::Vanir::TerminalColor_Bright_Blue), ::Vanir::Logger::LogHeader("INFO", __PRETTY_FUNCTION__, __LINE__), ::Vanir::LogColor(), __VA_ARGS__); \
    ::Vanir::Logger::InfoCount += 1; \
}
#define ULOG_VERBOSE(...) { \
    ::Vanir::Logger::ULog(::Vanir::LogColor(::Vanir::TerminalColor_Bright_Blue), ::Vanir::Logger::LogHeader("VERBOSE", __PRETTY_FUNCTION__, __LINE__), ::Vanir::LogColor(), __VA_ARGS__); \
    ::Vanir::Logger::WarningCount += 1; \
}
#define ULOG_WARNING(...) { \
    ::Vanir::Logger::ULog(::Vanir::LogColor(::Vanir::TerminalColor_Yellow), ::Vanir::Logger::LogHeader("WARNING", __PRETTY_FUNCTION__, __LINE__), ::Vanir::LogColor(), __VA_ARGS__); \
    ::Vanir::Logger::WarningCount += 1; \
}
#define ULOG_ERROR(...) { \
    ::Vanir::Logger::ULog(::Vanir::LogColor(::Vanir::TerminalColor_Red), ::Vanir::Logger::LogHeader("ERROR", __PRETTY_FUNCTION__, __LINE__), ::Vanir::LogColor(), __VA_ARGS__); \
    ::Vanir::Logger::ErrorCount += 1; \
}
#else
#define ULOG_INFO(...) { \
    ::Vanir::Logger::ULog(::Vanir::Logger::LogHeader("INFO"), __VA_ARGS__); \
    ::Vanir::Logger::InfoCount += 1; \
}
#define ULOG_VERBOSE(...) { \
    ::Vanir::Logger::ULog(::Vanir::LogColor(::Vanir::TerminalColor_Bright_Blue), ::Vanir::Logger::LogHeader("VERBOSE"), ::Vanir::LogColor(), __VA_ARGS__); \
    ::Vanir::Logger::WarningCount += 1; \
}
#define ULOG_WARNING(...) { \
    ::Vanir::Logger::ULog(::Vanir::LogColor(::Vanir::TerminalColor_Yellow), ::Vanir::Logger::LogHeader("WARNING"), __VA_ARGS__); \
    ::Vanir::Logger::WarningCount += 1; \
}
#define ULOG_ERROR(...) { \
    ::Vanir::Logger::ULog(::Vanir::LogColor(::Vanir::TerminalColor_Red), ::Vanir::Logger::LogHeader("ERROR"), __VA_ARGS__); \
    ::Vanir::Logger::ErrorCount += 1; \
}
#endif
#else
#define ULOG(...) LOG(__VA_ARGS__)
#define ULOG_INFO(...) LOG_INFO(__VA_ARGS__)
#define ULOG_VERBOSE(...) LOG_VERBOSE(__VA_ARGS__)
#define ULOG_WARNING(...) LOG_WARNING(__VA_ARGS__)
#define ULOG_ERROR(...) LOG_ERROR(__VA_ARGS__)
#endif

#endif /* VANIR_LOGGER_LOGGER_H. */
