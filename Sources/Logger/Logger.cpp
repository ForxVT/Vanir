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

#include <cstdarg>
#include <time.h>
#include <iostream>
#include <Vanir/Logger/Logger.h>
#include <Vanir/FileSystem/FileSystem.h>

namespace Vanir {
    std::ofstream Logger::m_file = std::ofstream();
    bool Logger::m_writingToFile = false;
    time_t Logger::m_time;
    bool Logger::m_fileOpened = false;
    bool Logger::m_log = true;
    int Logger::ErrorCount = 0;
    int Logger::WarningCount = 0;
    int Logger::InfoCount = 0;

    void Logger::Start(const std::string& filepath) {
        std::cout << LogColor();

        if (filepath.empty())
            m_log = false;

        if (m_log) {
            auto dir = Vanir::FileSystem::GetDirectoryPathFromFilePath(filepath);

            if (!dir.empty() && !Vanir::FileSystem::DirectoryExist(dir)) {
                Vanir::FileSystem::AddDirectory(dir);
            }

            m_file.open(filepath, std::ofstream::out | std::ofstream::trunc);
            m_fileOpened = true;
        }
    }

    void Logger::StartNoLog() {
        Start(std::string());
    }

    void Logger::Stop() {
        if (m_log) {
            m_file.close();
            m_fileOpened = false;
        }
    }

    void Logger::ResetCounters() {
        ErrorCount = 0;
        WarningCount = 0;
        InfoCount = 0;
    }

    std::string Logger::LogHeader(const std::string &message, const std::string &function, int line) {
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

    bool Logger::IsWritingToFile() {
        return m_writingToFile;
    }

} /* Namespace Vanir. */
