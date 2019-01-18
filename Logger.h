#ifndef VANIR_LOGGER_H
#define VANIR_LOGGER_H

#include <fstream>
#include <string>
#include <Vanir/Macros.h>
#include <Vanir/StringUtils.h>
#include <iostream>
#ifdef PLATFORM_WINDOWS
#include <fcntl.h>
#endif

namespace Vanir
{
    class Logger
    {
    public:
        static void Start();
        static void Stop();
        static std::string LogHeader(const std::string& message, const std::string& function = std::string(), int line = -1);
        template <typename... Args>
        static void Log(Args&&... args)
        {
            ((std::cout << std::forward<Args>(args)), ...) << std::endl;
        }
#ifdef PLATFORM_WINDOWS
        template <typename... Args>
        static void ULog(Args&&... args)
        {
            _setmode(_fileno(stdout), _O_WTEXT);
            ((std::wcout << ::Vanir::StringUtils::StringToWString(std::forward<Args>(args))), ...) << std::endl;
            _setmode(_fileno(stdout), _O_TEXT);
        }
#endif

    private:
        static std::ofstream m_file;
        static time_t m_time;
    };

} /* Namespace Vanir. */

#define VANIR_LOG(...) ::Vanir::Logger::Log(__VA_ARGS__);
#if defined(CONFIGURATION_DEBUG)
#define VANIR_LOG_INFO(...) \
{ \
    std::cout << ::Vanir::Logger::LogHeader("INFO", __FUNCTION__, __LINE__); \
    ::Vanir::Logger::Log(__VA_ARGS__); \
}
#define VANIR_LOG_WARNING(...) \
{ \
    std::cout << ::Vanir::Logger::LogHeader("WARNING", __FUNCTION__, __LINE__); \
    ::Vanir::Logger::Log(__VA_ARGS__); \
}
#define VANIR_LOG_ERROR(...) \
{ \
    std::cout << ::Vanir::Logger::LogHeader("ERROR", __FUNCTION__, __LINE__); \
    ::Vanir::Logger::Log(__VA_ARGS__); \
}
#else
#define VANIR_LOG_INFO(...) \
{ \
    std::cout << ::Vanir::Logger::LogHeader("INFO"); \
    ::Vanir::Logger::Log(__VA_ARGS__); \
}
#define VANIR_LOG_WARNING(...) \
{ \
    std::cout << ::Vanir::Logger::LogHeader("WARNING"); \
    ::Vanir::Logger::Log(__VA_ARGS__); \
}
#define VANIR_LOG_ERROR(...) \
{ \
    std::cout << ::Vanir::Logger::LogHeader("ERROR"); \
    ::Vanir::Logger::Log(__VA_ARGS__); \
}
#endif

#ifdef PLATFORM_WINDOWS
#define VANIR_ULOG(...) ::Vanir::Logger::ULog(__VA_ARGS__);
#if defined(CONFIGURATION_DEBUG)
#define VANIR_ULOG_INFO(...) \
{ \
    std::wcout << ::Vanir::StringUtils::StringToWString(::Vanir::Logger::LogHeader("INFO", __FUNCTION__, __LINE__)); \
    ::Vanir::Logger::ULog(__VA_ARGS__); \
}
#define VANIR_ULOG_WARNING(...) \
{ \
    std::wcout << ::Vanir::StringUtils::StringToWString(::Vanir::Logger::LogHeader("WARNING", __FUNCTION__, __LINE__)); \
    ::Vanir::Logger::ULog(__VA_ARGS__); \
}
#define VANIR_ULOG_ERROR(...) \
{ \
    std::wcout << ::Vanir::StringUtils::StringToWString(::Vanir::Logger::LogHeader("ERROR", __FUNCTION__, __LINE__)); \
    ::Vanir::Logger::ULog(__VA_ARGS__); \
}
#else
#define VANIR_ULOG_INFO(...) \
{ \
    std::wcout << ::Vanir::Logger::LogHeader("INFO"); \
    ::Vanir::Logger::ULog(__VA_ARGS__); \
}
#define VANIR_ULOG_WARNING(...) \
{ \
    std::wcout << ::Vanir::Logger::LogHeader("WARNING"); \
    ::Vanir::Logger::ULog(__VA_ARGS__); \
}
#define VANIR_ULOG_ERROR(...) \
{ \
    std::wcout << ::Vanir::Logger::LogHeader("ERROR"); \
    ::Vanir::Logger::ULog(__VA_ARGS__); \
}
#endif
#else
#define VANIR_ULOG(...) VANIR_LOG(__VA_ARGS__)
#define VANIR_ULOG_INFO(...) VANIR_LOG_INFO(__VA_ARGS__)
#define VANIR_ULOG_WARNING(...) VANIR_LOG_WARNING(__VA_ARGS__)
#define VANIR_ULOG_ERROR(...) VANIR_LOG_ERROR(__VA_ARGS__)
#endif

#endif /* VANIR_LOGGER_H. */
