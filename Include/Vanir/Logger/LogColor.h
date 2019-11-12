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
#include <Vanir/Logger/TerminalColor.h>

namespace Vanir {
    class LogColor {
    public:
        explicit LogColor(TerminalColor foregroundColor = TerminalColor_Default,
                             TerminalColor backgroundColor = TerminalColor_Default);

        friend std::ostream& operator<<(std::ostream& os, const LogColor& loggerColor);
        friend std::basic_ostream<wchar_t>& operator<<(std::basic_ostream<wchar_t>& os, const LogColor& loggerColor);

    private:
        TerminalColor m_foregroundColor;
        TerminalColor m_backgroundColor;
    };

} /* Namespace Vanir. */

#endif /* VANIR_LOGGER_LOGCOLOR_H. */