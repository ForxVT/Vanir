//==================================================================================//
//                                                                                  //
//  Copyright (c) 2019 Hugo Kindel <kindelhugo@gmail.com>                           //
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

#ifndef VANIR_COMMON_H
#define VANIR_COMMON_H

// Include commonly used STD files.
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>

// DLL export.
#if _WIN32
    #if _MSC_VER && !__INTEL_COMPILER
        #if VANIR_LIB_STATIC
            #define VANIR_EXPORT
        #else
            #if VANIR_LIB_IMPORT
                #define VANIR_EXPORT __declspec(dllimport)
            #else
                #define VANIR_EXPORT
            #endif
        #endif
    #else
        #if VANIR_LIB_SHARED
            #define VANIR_EXPORT __attribute__((dllexport))
        #else
            #if VANIR_LIB_IMPORT
                #define VANIR_EXPORT __attribute__((dllimport))
            #else
                #define VANIR_EXPORT
            #endif
        #endif
    #endif
#else
    #define VANIR_EXPORT __attribute__((visibility ("default")))
#endif

#if VANIR_BUILD_PROFILER
#include <easy/profiler.h>

#define PROFILE_ENABLE EASY_PROFILER_ENABLE
#define PROFILE_DUMP(NAME) profiler::dumpBlocksToFile(NAME)
#define PROFILE_LISTEN profiler::startListen()
#define PROFILE_FUNCTION(NAME) EASY_FUNCTION(NAME)
#define PROFILE_BLOCK(NAME) EASY_BLOCK(NAME)
#define PROFILE_BLOCK_END EASY_END_BLOCK
#else
#define PROFILE_ENABLE
#define PROFILE_DUMP(NAME)
#define PROFILE_LISTEN
#define PROFILE_FUNCTION(NAME)
#define PROFILE_BLOCK(NAME)
#define PROFILE_BLOCK_END
#endif

#endif /* VANIR_COMMON_H. */
