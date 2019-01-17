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
        auto hours = std::to_string(time->tm_hour);
        auto minutes = std::to_string(time->tm_min);
        auto seconds = std::to_string(time->tm_sec);
        auto logText = "[" + (hours.length() == 1 ? "0" + hours : hours) + ":" +
                (minutes.length() == 1 ? "0" + minutes : minutes) + ":" +
                (seconds.length() == 1 ? "0" + seconds : seconds) + "] " + text + "\n";
        char fileDest[1024];

        va_start(args, numArgs);
        vsprintf(fileDest, logText.c_str(), args);
        va_end(args);

        std::cout << fileDest;

        if (m_file.is_open())
            m_file << fileDest;

        return fileDest;
    }

    std::string Logger::LogInfo(const std::string&  text, int numArgs, ...)
    {
        m_time = time(nullptr);
        auto time = localtime(&m_time);
        va_list args;
        auto hours = std::to_string(time->tm_hour);
        auto minutes = std::to_string(time->tm_min);
        auto seconds = std::to_string(time->tm_sec);
        auto infoText = "[INFO | " + (hours.length() == 1 ? "0" + hours : hours) + ":" +
                (minutes.length() == 1 ? "0" + minutes : minutes) + ":" +
                (seconds.length() == 1 ? "0" + seconds : seconds) + "] " + text + "\n";
        char fileDest[1024];

        va_start(args, numArgs);
        vsprintf(fileDest, infoText.c_str(), args);
        va_end(args);

        std::cout << fileDest;

        if (m_file.is_open())
            m_file << fileDest;

        return fileDest;
    }

    std::string Logger::LogWarning(const std::string& text, int numArgs, ...)
    {
        m_time = time(nullptr);
        auto time = localtime(&m_time);
        va_list args;
        auto hours = std::to_string(time->tm_hour);
        auto minutes = std::to_string(time->tm_min);
        auto seconds = std::to_string(time->tm_sec);
        auto warningText = "[WARNING | " + (hours.length() == 1 ? "0" + hours : hours) + ":" +
                (minutes.length() == 1 ? "0" + minutes : minutes) + ":" +
                (seconds.length() == 1 ? "0" + seconds : seconds) + "] " + text + "\n";
        char fileDest[1024];

        va_start(args, numArgs);
        vsprintf(fileDest, warningText.c_str(), args);
        va_end(args);

        std::cout << fileDest;

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
        auto hours = std::to_string(time->tm_hour);
        auto minutes = std::to_string(time->tm_min);
        auto seconds = std::to_string(time->tm_sec);
        auto errorText = "[ERROR | " + (hours.length() == 1 ? "0" + hours : hours) + ":" +
                (minutes.length() == 1 ? "0" + minutes : minutes) + ":" +
                (seconds.length() == 1 ? "0" + seconds : seconds) + "] " + text + "\n";

        va_start(args, numArgs);
        vsprintf(fileDest, errorText.c_str(), args);
        va_end(args);

        std::cout << fileDest;

        if (m_file.is_open())
            m_file << fileDest;

        return fileDest;
    }

    std::string Logger::Log(const std::string&  text, const std::string&  function, const int line, int numArgs, ...)
    {
        m_time = time(nullptr);
        auto time = localtime(&m_time);
        va_list args;
        auto hours = std::to_string(time->tm_hour);
        auto minutes = std::to_string(time->tm_min);
        auto seconds = std::to_string(time->tm_sec);
        auto logText = "[" + function + " | Line " + std::to_string(line) + " | " +
                (hours.length() == 1 ? "0" + hours : hours) + ":" +
                (minutes.length() == 1 ? "0" + minutes : minutes) + ":" +
                (seconds.length() == 1 ? "0" + seconds : seconds) + "] " + text + "\n";
        char fileDest[1024];

        va_start(args, numArgs);
        vsprintf(fileDest, logText.c_str(), args);
        va_end(args);

        std::cout << fileDest;

        if (m_file.is_open())
            m_file << fileDest;

        return fileDest;
    }

    std::string Logger::LogInfo(const std::string&  text, const std::string&  function, const int line, int numArgs, ...)
    {
        m_time = time(nullptr);
        auto time = localtime(&m_time);
        va_list args;
        auto hours = std::to_string(time->tm_hour);
        auto minutes = std::to_string(time->tm_min);
        auto seconds = std::to_string(time->tm_sec);
        auto infoText = "[INFO | " + function + " | Line " + std::to_string(line) + " | " +
                (hours.length() == 1 ? "0" + hours : hours) + ":" +
                (minutes.length() == 1 ? "0" + minutes : minutes) + ":" +
                (seconds.length() == 1 ? "0" + seconds : seconds) + "] " + text + "\n";
        char fileDest[1024];

        va_start(args, numArgs);
        vsprintf(fileDest, infoText.c_str(), args);
        va_end(args);

        std::cout << fileDest;

        if (m_file.is_open())
            m_file << fileDest;

        return fileDest;
    }

    std::string Logger::LogWarning(const std::string&  text, const std::string&  function, const int line, int numArgs, ...)
    {
        m_time = time(nullptr);
        auto time = localtime(&m_time);
        va_list args;
        auto hours = std::to_string(time->tm_hour);
        auto minutes = std::to_string(time->tm_min);
        auto seconds = std::to_string(time->tm_sec);
        auto warningText = "[WARNING | " + function + " | Line " + std::to_string(line) + " | " +
                (hours.length() == 1 ? "0" + hours : hours) + ":" +
                (minutes.length() == 1 ? "0" + minutes : minutes) + ":" +
                (seconds.length() == 1 ? "0" + seconds : seconds) + "] " + text + "\n";
        char fileDest[1024];

        va_start(args, numArgs);
        vsprintf(fileDest, warningText.c_str(), args);
        va_end(args);

        std::cout << fileDest;

        if (m_file.is_open())
            m_file << fileDest;

        return fileDest;
    }

    std::string Logger::LogError(const std::string& text, const std::string& function, const int line, int numArgs, ...)
    {
        m_time = time(nullptr);
        auto time = localtime(&m_time);
        va_list args;
        auto hours = std::to_string(time->tm_hour);
        auto minutes = std::to_string(time->tm_min);
        auto seconds = std::to_string(time->tm_sec);
        auto errorText = "[ERROR | " + function + " | Line " + std::to_string(line) + " | " +
                (hours.length() == 1 ? "0" + hours : hours) + ":" +
                (minutes.length() == 1 ? "0" + minutes : minutes) + ":" +
                (seconds.length() == 1 ? "0" + seconds : seconds) + "] " + text + "\n";
        char fileDest[1024];

        va_start(args, numArgs);
        vsprintf(fileDest, errorText.c_str(), args);
        va_end(args);

        std::cout << fileDest;

        if (m_file.is_open())
            m_file << fileDest;

        return fileDest;
    }

    std::string Logger::LogDefault(const std::string& text, int numArgs, ...)
    {
        va_list args;
        auto logText = text + "\n";
        char fileDest[1024];

        va_start(args, numArgs);
        vsprintf(fileDest, logText.c_str(), args);
        va_end(args);

        std::cout << fileDest;

        if (m_file.is_open())
            m_file << fileDest;

        return fileDest;
    }

} /* Namespace Vanir. */