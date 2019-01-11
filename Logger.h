// TODO: Unicode support (by checking _UNICODE)
#ifndef VANIR_LOGGER_H
#define VANIR_LOGGER_H

#include <fstream>
#include <string>
#include <Vanir/Macros.h>

namespace Vanir
{
    class Logger
    {
    public:
        static void Start();
        static void Stop();
        static std::string Log(const std::string& text, int numArgs, ...);
        static std::string LogInfo(const std::string& text, int numArgs, ...);
        static std::string LogWarning(const std::string& text, int numArgs, ...);
        static std::string LogError(const std::string& text, int numArgs, ...);
        static std::string Log(const std::string& text, const std::string& function, int line, int numArgs, ...);
        static std::string LogInfo(const std::string& text, const std::string& function, int line, int numArgs, ...);
        static std::string LogWarning(const std::string& text, const std::string& function, int line, int numArgs, ...);
        static std::string LogError(const std::string& text, const std::string& function, int line, int numArgs, ...);
        static std::string LogDefault(const std::string& text, int numArgs, ...);

    private:
        static std::ofstream m_file;
        static time_t m_time;
    };

} /* Namespace Vanir. */

#if defined(_WIN32)
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define expand(x) \
x
#define prefix(...) \
0, ##__VA_ARGS__
#define lastof10(a, b, c, d, e, f, g, h, i, j, ...) \
j
#define sub_nbarg(...) \
expand(lastof10(__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define nbarg(...) \
sub_nbarg(prefix(__VA_ARGS__))

#if defined(CONFIGURATION_DEBUG)
#define VANIR_LOG_TEXT(LOGTEXT, ...) \
::Vanir::Logger::Log(LOGTEXT, __FUNCTION__, __LINE__, nbarg(__VA_ARGS__), __VA_ARGS__);
#define VANIR_LOG_INFO(LOGTEXT, ...) \
::Vanir::Logger::LogInfo(LOGTEXT, __FUNCTION__, __LINE__, nbarg(__VA_ARGS__), __VA_ARGS__);
#define VANIR_LOG_WARNING(LOGTEXT, ...) \
::Vanir::Logger::LogWarning(LOGTEXT, __FUNCTION__, __LINE__, nbarg(__VA_ARGS__), __VA_ARGS__);
#define VANIR_LOG_ERROR(LOGTEXT, ...) \
::Vanir::Logger::LogError(LOGTEXT, __FUNCTION__, __LINE__, nbarg(__VA_ARGS__), __VA_ARGS__);
#else
#define VANIR_LOG_TEXT(LOGTEXT, ...) \
::Vanir::Logger::Log(LOGTEXT, nbarg(__VA_ARGS__), ##__VA_ARGS__);
#define VANIR_LOG_INFO(LOGTEXT, ...) \
::Vanir::Logger::LogInfo(LOGTEXT, nbarg(__VA_ARGS__), ##__VA_ARGS__);
#define VANIR_LOG_WARNING(LOGTEXT, ...) \
::Vanir::Logger::LogWarning(LOGTEXT, nbarg(__VA_ARGS__), ##__VA_ARGS__);
#define VANIR_LOG_ERROR(LOGTEXT, ...) \
::Vanir::Logger::LogError(LOGTEXT, nbarg(__VA_ARGS__), ##__VA_ARGS__);
#endif
#define VANIR_LOG_DEFAULT(LOGTEXT, ...) \
::Vanir::Logger::LogDefault(LOGTEXT, nbarg(__VA_ARGS__), ##__VA_ARGS__);

#endif /* VANIR_LOGGER_H. */