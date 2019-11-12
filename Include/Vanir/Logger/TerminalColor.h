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

#ifndef VANIR_TERMINALCOLOR_H
#define VANIR_TERMINALCOLOR_H

#include <Vanir/Common.h>

namespace Vanir {
    /// List of colors used by terminals.
    enum TerminalColor {
#ifdef _WIN32
        TerminalColor_Black,
        TerminalColor_Blue,
        TerminalColor_Green,
        TerminalColor_Cyan,
        TerminalColor_Red,
        TerminalColor_Magenta,
        TerminalColor_Yellow,
        TerminalColor_White,
        TerminalColor_Gray,
        TerminalColor_Bright_Blue,
        TerminalColor_Bright_Green,
        TerminalColor_Bright_Cyan,
        TerminalColor_Bright_Red,
        TerminalColor_Bright_Magenta,
        TerminalColor_Bright_Yellow,
        TerminalColor_Bright_Gray,
        TerminalColor_Default = 20
#else
        TerminalColor_Black,
        TerminalColor_Red,
        TerminalColor_Green,
        TerminalColor_Yellow,
        TerminalColor_Blue,
        TerminalColor_Magenta,
        TerminalColor_Cyan,
        TerminalColor_Bright_Gray,
        TerminalColor_Gray = 10,
        TerminalColor_Bright_Red,
        TerminalColor_Bright_Green,
        TerminalColor_Bright_Yellow,
        TerminalColor_Bright_Blue,
        TerminalColor_Bright_Magenta,
        TerminalColor_Bright_Cyan,
        TerminalColor_Bright_White,
        TerminalColor_Default = 20
#endif
    };

} /* Namespace Vanir. */

#endif /* VANIR_TERMINALCOLOR_H. */
