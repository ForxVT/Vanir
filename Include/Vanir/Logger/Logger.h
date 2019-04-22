//==================================================================================//
//                                                                                  //
//  Copyright (c) 2019 Hugo Kindel <kindelhugo@gmail.com>                           //
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

#include <Vanir/Common.h>
#include <Vanir/Logger/LoggerColor.h>
#include <Vanir/Logger/LoggerTypes.h>
#include <Vanir/String/StringUtils.h>
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

namespace Vanir
{
    class Logger
    {
    public:
        static void Start(const std::string& filepath = "logs.log");
        static void StartNoLog();
        static void Stop();
        static void ResetCounters();
        static void IncreaseCounter(LoggerTypes counter);
        static std::string LogHeader(const std::string& message, const std::string& function = std::string(), int line = -1);
        template <typename... Args>
        static void Log(Args&&... args)
        {
            ((std::cout << std::forward<Args>(args)), ...) << Vanir::LoggerColor() << std::endl;

            m_writingToFile = true;

            if (m_fileOpened)
                ((m_file << std::forward<Args>(args)), ...) << std::endl;

            m_writingToFile = false;
        }
        static bool IsWritingToFile();
#ifdef _WIN32
        template <class T>
        static std::basic_ostream<wchar_t>& ULogConverter(T&& arg)
        {
            return std::wcout << arg;
        }
        static std::basic_ostream<wchar_t>& ULogConverter(std::string arg)
        {
            return std::wcout << ::Vanir::StringUtils::StringToWString(arg);
        }
        static std::basic_ostream<wchar_t>& ULogConverter(const char* arg)
        {
            return std::wcout << ::Vanir::StringUtils::StringToWString(arg);
        }
        template <typename... Args>
        static void ULog(Args&&... args)
        {
            _setmode(_fileno(stdout), _O_WTEXT);
            ((ULogConverter(std::forward<Args>(args))), ...) << Vanir::LoggerColor() << std::endl;
            _setmode(_fileno(stdout), _O_TEXT);

            m_writingToFile = true;

            if (m_fileOpened)
                ((m_file << std::forward<Args>(args)), ...) << std::endl;

            m_writingToFile = false;
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

#define VANIR_LOG_RESETCOUNTERS() ::Vanir::Logger::ResetCounters();
#define VANIR_LOG_INCREASECOUNTER(TYPE) ::Vanir::Logger::IncreaseCounter(TYPE);

#define VANIR_LOG(...) ::Vanir::Logger::Log(__VA_ARGS__);
#if defined(_DEBUG)
#define VANIR_LOG_INFO(...) \
{ \
    ::Vanir::Logger::Log(::Vanir::Logger::LogHeader("INFO", __FUNCTION__, __LINE__), __VA_ARGS__); \
    ::Vanir::Logger::InfoCount += 1; \
}
#define VANIR_LOG_WARNING(...) \
{ \
    ::Vanir::Logger::Log(::Vanir::LoggerColor(::Vanir::LoggerColors_Yellow), ::Vanir::Logger::LogHeader("WARNING", __FUNCTION__, __LINE__), __VA_ARGS__); \
    ::Vanir::Logger::WarningCount += 1; \
}
#define VANIR_LOG_ERROR(...) \
{ \
    ::Vanir::Logger::Log(::Vanir::LoggerColor(::Vanir::LoggerColors_Red), ::Vanir::Logger::LogHeader("ERROR", __FUNCTION__, __LINE__), __VA_ARGS__); \
    ::Vanir::Logger::ErrorCount += 1; \
}
#else
#define VANIR_LOG_INFO(...) \
{ \
    ::Vanir::Logger::Log(::Vanir::Logger::LogHeader("INFO"), __VA_ARGS__); \
    ::Vanir::Logger::InfoCount += 1; \
}
#define VANIR_LOG_WARNING(...) \
{ \
    ::Vanir::Logger::Log(::Vanir::LoggerColor(::Vanir::LoggerColors_Yellow), ::Vanir::Logger::LogHeader("WARNING"), __VA_ARGS__); \
    ::Vanir::Logger::WarningCount += 1; \
}
#define VANIR_LOG_ERROR(...) \
{ \
    ::Vanir::Logger::Log(::Vanir::LoggerColor(::Vanir::LoggerColors_Red), ::Vanir::Logger::LogHeader("ERROR"), __VA_ARGS__); \
    ::Vanir::Logger::ErrorCount += 1; \
}
#endif

#ifdef _WIN32
#define VANIR_ULOG(...) ::Vanir::Logger::ULog(__VA_ARGS__);
#if defined(_DEBUG)
#define VANIR_ULOG_INFO(...) \
{ \
    ::Vanir::Logger::ULog(::Vanir::Logger::LogHeader("INFO", __FUNCTION__, __LINE__), __VA_ARGS__); \
    ::Vanir::Logger::InfoCount += 1; \
}
#define VANIR_ULOG_WARNING(...) \
{ \
    ::Vanir::Logger::ULog(::Vanir::LoggerColor(::Vanir::LoggerColors_Yellow), ::Vanir::Logger::LogHeader("WARNING", __FUNCTION__, __LINE__), __VA_ARGS__); \
    ::Vanir::Logger::WarningCount += 1; \
}
#define VANIR_ULOG_ERROR(...) \
{ \
    ::Vanir::Logger::ULog(::Vanir::LoggerColor(::Vanir::LoggerColors_Red), ::Vanir::Logger::LogHeader("ERROR", __FUNCTION__, __LINE__), __VA_ARGS__); \
    ::Vanir::Logger::ErrorCount += 1; \
}
#else
#define VANIR_ULOG_INFO(...) \
{ \
    ::Vanir::Logger::ULog(::Vanir::Logger::LogHeader("INFO"), __VA_ARGS__); \
    ::Vanir::Logger::InfoCount += 1; \
}
#define VANIR_ULOG_WARNING(...) \
{ \
    ::Vanir::Logger::ULog(::Vanir::LoggerColor(::Vanir::LoggerColors_Yellow), ::Vanir::Logger::LogHeader("WARNING"), __VA_ARGS__); \
    ::Vanir::Logger::WarningCount += 1; \
}
#define VANIR_ULOG_ERROR(...) \
{ \
    ::Vanir::Logger::ULog(::Vanir::LoggerColor(::Vanir::LoggerColors_Red), ::Vanir::Logger::LogHeader("ERROR"), __VA_ARGS__); \
    ::Vanir::Logger::ErrorCount += 1; \
}
#endif
#else
#define VANIR_ULOG(...) VANIR_LOG(__VA_ARGS__)
#define VANIR_ULOG_INFO(...) VANIR_LOG_INFO(__VA_ARGS__)
#define VANIR_ULOG_WARNING(...) VANIR_LOG_WARNING(__VA_ARGS__)
#define VANIR_ULOG_ERROR(...) VANIR_LOG_ERROR(__VA_ARGS__)
#endif

#endif /* VANIR_LOGGER_LOGGER_H. */
