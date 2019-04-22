//==================================================================================//
//                                                                                  //
//  Copyright (c) 2019 Hugo Kindel <kindelhugo@gmail.com>                           //
//                                                                                  //
//  This file is part of the Aesir project.                                         //
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

#ifndef VANIR_LOGGER_LOGGERCOLORS_H
#define VANIR_LOGGER_LOGGERCOLORS_H

#include <Vanir/Common.h>

namespace Vanir
{
#ifdef _WIN32
    enum LoggerColors
    {
        LoggerColors_Black,
        LoggerColors_Blue,
        LoggerColors_Green,
        LoggerColors_Cyan,
        LoggerColors_Red,
        LoggerColors_Magenta,
        LoggerColors_Yellow,
        LoggerColors_White,
        LoggerColors_Gray,
        LoggerColors_Bright_Blue,
        LoggerColors_Bright_Green,
        LoggerColors_Bright_Cyan,
        LoggerColors_Bright_Red,
        LoggerColors_Bright_Magenta,
        LoggerColors_Bright_Yellow,
        LoggerColors_Bright_Gray,
        LoggerColors_Default = 20
    };
#else
    enum LoggerColors
    {
        LoggerColors_Black,
        LoggerColors_Red,
        LoggerColors_Green,
        LoggerColors_Yellow,
        LoggerColors_Blue,
        LoggerColors_Magenta,
        LoggerColors_Cyan,
        LoggerColors_Bright_Gray,
        LoggerColors_Gray = 10,
        LoggerColors_Bright_Red,
        LoggerColors_Bright_Green,
        LoggerColors_Bright_Yellow,
        LoggerColors_Bright_Blue,
        LoggerColors_Bright_Magenta,
        LoggerColors_Bright_Cyan,
        LoggerColors_Bright_White,
        LoggerColors_Default = 20
    };
#endif

} /* Namespace Vanir. */

#endif /* VANIR_LOGGER_LOGGERCOLORS_H. */
