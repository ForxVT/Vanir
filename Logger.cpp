#include <Vanir/Logger.h>
#include <cstdarg>
#include <time.h>
#include <iostream>

namespace Vanir
{
    std::ofstream Logger::m_file = std::ofstream();
    time_t Logger::m_time;

    void Logger::Start()
    {
        m_file.open("Logs.log", std::ofstream::out | std::ofstream::trunc);
    }

    void Logger::Stop()
    {
        m_file.close();
    }

    std::string Logger::Log(const std::string&  text, int numArgs, ...)
    {
        m_time = time(nullptr);
        auto time = localtime(&m_time);
        va_list args;
        auto logText = "[" + std::to_string(time->tm_hour) + ":" + std::to_string(time->tm_min) + ":" + std::to_string(time->tm_sec) + "] " + text + "\n";
        const auto result = logText.c_str();
        char fileDest[1024];

        va_start(args, numArgs);
        vsprintf(fileDest, result, args);
        va_end(args);

        std::cout << result;

        if (m_file.is_open())
            m_file << fileDest;

        return fileDest;
    }

    std::string Logger::LogInfo(const std::string&  text, int numArgs, ...)
    {
        m_time = time(nullptr);
        auto time = localtime(&m_time);
        va_list args;
        auto infoText = "[INFO | " + std::to_string(time->tm_hour) + ":" + std::to_string(time->tm_min) + ":" + std::to_string(time->tm_sec) + "] " + text + "\n";
        const auto result = infoText.c_str();
        char fileDest[1024];

        va_start(args, numArgs);
        vsprintf(fileDest, result, args);
        va_end(args);

        std::cout << result;

        if (m_file.is_open())
            m_file << fileDest;

        return fileDest;
    }

    std::string Logger::LogWarning(const std::string& text, int numArgs, ...)
    {
        m_time = time(nullptr);
        auto time = localtime(&m_time);
        va_list args;
        auto warningText = "[WARNING | " + std::to_string(time->tm_hour) + ":" + std::to_string(time->tm_min) + ":" + std::to_string(time->tm_sec) + "] " + text + "\n";
        const auto result = warningText.c_str();
        char fileDest[1024];

        va_start(args, numArgs);
        vsprintf(fileDest, result, args);
        va_end(args);

        std::cout << result;

        if (m_file.is_open())
            m_file << fileDest;

        return fileDest;
    }

    std::string Logger::LogError(const std::string&  text, int numArgs, ...)
    {
        m_time = time(nullptr);
        auto time = localtime(&m_time);
        va_list args;
        char fileDest[1024];
        auto errorText = "[ERROR | " + std::to_string(time->tm_hour) + ":" + std::to_string(time->tm_min) + ":" + std::to_string(time->tm_sec) + "] " + text + "\n";

        const auto result = errorText.c_str();

        va_start(args, numArgs);
        vsprintf(fileDest, result, args);
        va_end(args);

        std::cout << result;

        if (m_file.is_open())
            m_file << fileDest;

        return fileDest;
    }

    std::string Logger::Log(const std::string&  text, const std::string&  function, const int line, int numArgs, ...)
    {
        m_time = time(nullptr);
        auto time = localtime(&m_time);
        va_list args;
        auto logText = "[" + function + " | Line " + std::to_string(line) + " | " + std::to_string(time->tm_hour) + ":" + std::to_string(time->tm_min) + ":" + std::to_string(time->tm_sec) + "] " + text + "\n";
        const auto result = logText.c_str();
        char fileDest[1024];

        va_start(args, numArgs);
        vsprintf(fileDest, result, args);
        va_end(args);

        std::cout << result;

        if (m_file.is_open())
            m_file << fileDest;

        return fileDest;
    }

    std::string Logger::LogInfo(const std::string&  text, const std::string&  function, const int line, int numArgs, ...)
    {
        m_time = time(nullptr);
        auto time = localtime(&m_time);
        va_list args;
        auto infoText = "[INFO | " + function + " | Line " + std::to_string(line) + " | " + std::to_string(time->tm_hour) + ":" + std::to_string(time->tm_min) + ":" + std::to_string(time->tm_sec) + "] " + text + "\n";
        const auto result = infoText.c_str();
        char fileDest[1024];

        va_start(args, numArgs);
        vsprintf(fileDest, result, args);
        va_end(args);

        std::cout << result;

        if (m_file.is_open())
            m_file << fileDest;

        return fileDest;
    }

    std::string Logger::LogWarning(const std::string&  text, const std::string&  function, const int line, int numArgs, ...)
    {
        m_time = time(nullptr);
        auto time = localtime(&m_time);
        va_list args;
        auto warningText = "[WARNING | " + function + " | Line " + std::to_string(line) + " | " + std::to_string(time->tm_hour) + ":" + std::to_string(time->tm_min) + ":" + std::to_string(time->tm_sec) + "] " + text + "\n";
        const auto result = warningText.c_str();
        char fileDest[1024];

        va_start(args, numArgs);
        vsprintf(fileDest, result, args);
        va_end(args);

        std::cout << result;

        if (m_file.is_open())
            m_file << fileDest;

        return fileDest;
    }

    std::string Logger::LogError(const std::string& text, const std::string& function, const int line, int numArgs, ...)
    {
        m_time = time(nullptr);
        auto time = localtime(&m_time);
        va_list args;
        auto errorText = "[ERROR | " + function + " | Line " + std::to_string(line) + " | " + std::to_string(time->tm_hour) + ":" + std::to_string(time->tm_min) + ":" + std::to_string(time->tm_sec) + "] " + text + "\n";
        const auto result = errorText.c_str();
        char fileDest[1024];

        va_start(args, numArgs);
        vsprintf(fileDest, result, args);
        va_end(args);

        std::cout << result;

        if (m_file.is_open())
            m_file << fileDest;

        return fileDest;
    }

    std::string Logger::LogDefault(const std::string& text, int numArgs, ...)
    {
        va_list args;
        auto logText = text + "\n";
        char fileDest[1024];

        const auto result = logText.c_str();

        va_start(args, numArgs);
        vsprintf(fileDest, result, args);
        va_end(args);

        std::cout << result;

        if (m_file.is_open())
            m_file << fileDest;

        return fileDest;
    }

} /* Namespace Vanir. */