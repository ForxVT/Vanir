#ifndef VANIR_LOGGER_H
#define VANIR_LOGGER_H

#include <fstream>
#include <string>
#include <Vanir/Macros.h>
#include <Vanir/StringUtils.h>
#include <Vanir/LoggerColor.h>
#include <iostream>
#ifdef PLATFORM_WINDOWS
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
        static void Stop();
        static std::string LogHeader(const std::string& message, const std::string& function = std::string(), int line = -1);
        template <typename... Args>
        static void Log(Args&&... args)
        {
            ((std::cout << std::forward<Args>(args)), ...) << Vanir::LoggerColor() << std::endl;

            m_writingToFile = true;

            ((m_file << std::forward<Args>(args)), ...) << std::endl;

            m_writingToFile = false;
        }
        static bool IsWritingToFile();
#ifdef PLATFORM_WINDOWS
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

            ((m_file << std::forward<Args>(args)), ...) << std::endl;

            m_writingToFile = false;
        }
#endif

    private:
        static std::ofstream m_file;
        static bool m_writingToFile;
        static time_t m_time;
    };

} /* Namespace Vanir. */

#define VANIR_LOG(...) ::Vanir::Logger::Log(__VA_ARGS__);
#if defined(CONFIGURATION_DEBUG)
#define VANIR_LOG_INFO(...) \
{ \
    ::Vanir::Logger::Log(::Vanir::Logger::LogHeader("INFO", __FUNCTION__, __LINE__), __VA_ARGS__); \
}
#define VANIR_LOG_WARNING(...) \
{ \
    ::Vanir::Logger::Log(::Vanir::LoggerColor(::Vanir::LoggerColors_Yellow), ::Vanir::Logger::LogHeader("WARNING", __FUNCTION__, __LINE__), __VA_ARGS__); \
}
#define VANIR_LOG_ERROR(...) \
{ \
    ::Vanir::Logger::Log(::Vanir::LoggerColor(::Vanir::LoggerColors_Red), ::Vanir::Logger::LogHeader("ERROR", __FUNCTION__, __LINE__), __VA_ARGS__); \
}
#else
#define VANIR_LOG_INFO(...) \
{ \
    ::Vanir::Logger::Log(::Vanir::Logger::LogHeader("INFO"), __VA_ARGS__); \
}
#define VANIR_LOG_WARNING(...) \
{ \
    ::Vanir::Logger::Log(::Vanir::LoggerColor(::Vanir::LoggerColors_Yellow), ::Vanir::Logger::LogHeader("WARNING"), __VA_ARGS__); \
}
#define VANIR_LOG_ERROR(...) \
{ \
    ::Vanir::Logger::Log(::Vanir::LoggerColor(::Vanir::LoggerColors_Red), ::Vanir::Logger::LogHeader("ERROR"), __VA_ARGS__); \
}
#endif

#ifdef PLATFORM_WINDOWS
#define VANIR_ULOG(...) ::Vanir::Logger::ULog(__VA_ARGS__);
#if defined(CONFIGURATION_DEBUG)
#define VANIR_ULOG_INFO(...) \
{ \
    ::Vanir::Logger::ULog(::Vanir::Logger::LogHeader("INFO", __FUNCTION__, __LINE__), __VA_ARGS__); \
}
#define VANIR_ULOG_WARNING(...) \
{ \
    ::Vanir::Logger::ULog(::Vanir::LoggerColor(::Vanir::LoggerColors_Yellow), ::Vanir::Logger::LogHeader("WARNING", __FUNCTION__, __LINE__), __VA_ARGS__); \
}
#define VANIR_ULOG_ERROR(...) \
{ \
    ::Vanir::Logger::ULog(::Vanir::LoggerColor(::Vanir::LoggerColors_Red), ::Vanir::Logger::LogHeader("ERROR", __FUNCTION__, __LINE__), __VA_ARGS__); \
}
#else
#define VANIR_ULOG_INFO(...) \
{ \
    ::Vanir::Logger::ULog(::Vanir::Logger::LogHeader("INFO"), __VA_ARGS__); \
}
#define VANIR_ULOG_WARNING(...) \
{ \
    ::Vanir::Logger::ULog(::Vanir::LoggerColor(::Vanir::LoggerColors_Yellow), ::Vanir::Logger::LogHeader("WARNING"), __VA_ARGS__); \
}
#define VANIR_ULOG_ERROR(...) \
{ \
    ::Vanir::Logger::ULog(::Vanir::LoggerColor(::Vanir::LoggerColors_Red), ::Vanir::Logger::LogHeader("ERROR"), __VA_ARGS__); \
}
#endif
#else
#define VANIR_ULOG(...) VANIR_LOG(__VA_ARGS__)
#define VANIR_ULOG_INFO(...) VANIR_LOG_INFO(__VA_ARGS__)
#define VANIR_ULOG_WARNING(...) VANIR_LOG_WARNING(__VA_ARGS__)
#define VANIR_ULOG_ERROR(...) VANIR_LOG_ERROR(__VA_ARGS__)
#endif

#endif /* VANIR_LOGGER_H. */
