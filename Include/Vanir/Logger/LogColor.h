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

#ifndef VANIR_LOGGER_LOGCOLOR_H
#define VANIR_LOGGER_LOGCOLOR_H

#include <ostream>
#include <Vanir/Common.h>

namespace Vanir {
    /// List of colors used by terminals.
    enum LogColorEnum {
#ifdef _WIN32
        LogColor_Black,
        LogColor_Blue,
        LogColor_Green,
        LogColor_Cyan,
        LogColor_Red,
        LogColor_Magenta,
        LogColor_Yellow,
        LogColor_White,
        LogColor_Gray,
        LogColor_Bright_Blue,
        LogColor_Bright_Green,
        LogColor_Bright_Cyan,
        LogColor_Bright_Red,
        LogColor_Bright_Magenta,
        LogColor_Bright_Yellow,
        LogColor_Bright_Gray,
        LogColor_Default = 20
#else
        LogColor_Black,
        LogColor_Red,
        LogColor_Green,
        LogColor_Yellow,
        LogColor_Blue,
        LogColor_Magenta,
        LogColor_Cyan,
        LogColor_Bright_Gray,
        LogColor_Gray = 10,
        LogColor_Bright_Red,
        LogColor_Bright_Green,
        LogColor_Bright_Yellow,
        LogColor_Bright_Blue,
        LogColor_Bright_Magenta,
        LogColor_Bright_Cyan,
        LogColor_Bright_White,
        LogColor_Default = 20
#endif
    };
    
    class LogColor {
    public:
        explicit LogColor(LogColorEnum foregroundColor = LogColor_Default,
                          LogColorEnum backgroundColor = LogColor_Default);

        friend std::ostream& operator<<(std::ostream& os, const LogColor& loggerColor);
        friend std::basic_ostream<wchar_t>& operator<<(std::basic_ostream<wchar_t>& os, const LogColor& loggerColor);

    private:
        LogColorEnum m_foregroundColor;
        LogColorEnum m_backgroundColor;
    };

} /* Namespace Vanir. */

#endif /* VANIR_LOGGER_LOGCOLOR_H. */