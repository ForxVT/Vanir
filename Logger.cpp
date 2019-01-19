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

    std::string Logger::LogHeader(const std::string &message, const std::string &function, int line)
    {
        m_time = time(nullptr);
        auto time = localtime(&m_time);
        auto hours = std::to_string(time->tm_hour);
        auto minutes = std::to_string(time->tm_min);
        auto seconds = std::to_string(time->tm_sec);
        auto infoText = "[" + message + " | " +
                        (function.empty() ? "" : function + " | ") +
                        (line == -1 ? "" : "Line " + std::to_string(line) + " | ") +
                        (hours.length() == 1 ? "0" + hours : hours) + ":" +
                        (minutes.length() == 1 ? "0" + minutes : minutes) + ":" +
                        (seconds.length() == 1 ? "0" + seconds : seconds) + "] ";

        return infoText;
    }

} /* Namespace Vanir. */
