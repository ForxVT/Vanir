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

#include <Vanir/Logger/LogColor.h>
#include <Vanir/Logger/Logger.h>

namespace Vanir {
    LogColor::LogColor(TerminalColor foregroundColor, TerminalColor backgroundColor) :
            m_foregroundColor(foregroundColor), m_backgroundColor(backgroundColor) {

    }

    std::ostream &operator<<(std::ostream &os, const LogColor &loggerColor) {
        if (!Logger::IsWritingToFile()) {
#ifdef _WIN32
            HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

            int foregroundColor = 15;
            int backgroundColor = 0;

            if (loggerColor.m_foregroundColor != 20)
                foregroundColor = loggerColor.m_foregroundColor;

            if (loggerColor.m_backgroundColor != 20)
                backgroundColor = loggerColor.m_backgroundColor;

            SetConsoleTextAttribute(hStdout, foregroundColor + backgroundColor);

            return os;
#else
            int foregroundColor = 39;
            int backgroundColor = 49;

            if (loggerColor.m_foregroundColor < 10)
                foregroundColor = loggerColor.m_foregroundColor + 30;
            else if (loggerColor.m_foregroundColor != 20)
                foregroundColor = loggerColor.m_foregroundColor + 80;

            if (loggerColor.m_backgroundColor < 10)
                backgroundColor = loggerColor.m_backgroundColor + 40;
            else if (loggerColor.m_backgroundColor != 20)
                backgroundColor = loggerColor.m_backgroundColor + 90;

            return os << "\u001b[0;" + std::to_string(foregroundColor) + ";" + std::to_string(backgroundColor) + "m";
#endif
        }
        else {
            return os;
        }
    }

    std::basic_ostream<wchar_t> &operator<<(std::basic_ostream<wchar_t> &os, const LogColor &loggerColor) {
        if (!Logger::IsWritingToFile()) {
#ifdef _WIN32
            HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hStdout, loggerColor.m_foregroundColor + loggerColor.m_backgroundColor);

            int foregroundColor = 15;
            int backgroundColor = 0;

            if (loggerColor.m_foregroundColor != 20)
                foregroundColor = loggerColor.m_foregroundColor;

            if (loggerColor.m_backgroundColor != 20)
                backgroundColor = loggerColor.m_backgroundColor;

            SetConsoleTextAttribute(hStdout, foregroundColor + backgroundColor);

            return os;
#endif
        }
        else {
            return os;
        }
    }

} /* Namespace Vanir. */