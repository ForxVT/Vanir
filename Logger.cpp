#include <Vanir/Logger.h>
#include <cstdarg>
#include <time.h>
#include <iostream>
#include "FileUtils.h"
#include "Logger.h"


namespace Vanir
{
    std::ofstream Logger::m_file = std::ofstream();
    bool Logger::m_writingToFile = false;
    time_t Logger::m_time;
    bool Logger::m_fileOpened = false;

    void Logger::Start(const std::string& filepath)
    {
        auto dir = Vanir::FileUtils::GetDirectoryPathFromFilePath(filepath);

        if (!dir.empty())
        {
            if (!Vanir::FileUtils::FolderExist(dir))
                Vanir::FileUtils::AddFolder(dir);
        }

        m_file.open(filepath, std::ofstream::out | std::ofstream::trunc);

        m_fileOpened = true;
    }

    void Logger::Stop()
    {
        m_file.close();

        m_fileOpened = false;
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

    bool Logger::IsWritingToFile()
    {
        return m_writingToFile;
    }

} /* Namespace Vanir. */
