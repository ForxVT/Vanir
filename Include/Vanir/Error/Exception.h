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

#ifndef VANIR_ERROR_EXCEPTION_H
#define VANIR_ERROR_EXCEPTION_H

#include <Vanir/Common.h>
#include <Vanir/Logger/Logger.h>

namespace Vanir {
    class Exception : public std::exception {
    public:
        template <typename... Args>
        Exception(const std::string &type, const std::string &source, const std::string &file, int line, Args&&... args);
        ~Exception() noexcept override = default;

        const char* what() const noexcept override;

    protected:
        mutable std::string m_error;
    };

    template <typename... Args>
    Exception::Exception(const std::string &type, const std::string &source, const std::string &file, int line, Args&&... args) {
        std::stringstream error;

        error << "FATAL ERROR !\n\n";
        error << "Exception type: " << type << "\n";
        error << "Message: ";
        ((error << std::forward<Args>(args)), ...)  << "\n";
        error << "In Method: " << source << "\n";
        error << "In File: " << file << " (line " << line << ")";

        m_error = error.str();
    }

} /* Namespace Vanir. */

#define THROW_EXCEPTION(type, ...) { \
    ULOG_ERROR("EXCEPTION - ", type, ": ", ##__VA_ARGS__); \
    throw ::Vanir::Exception(type, __PRETTY_FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__); \
}

#define THROW_ERROR(type, ...) { \
    try { \
        ULOG_ERROR("EXCEPTION - ", type, ": ", ##__VA_ARGS__); \
        throw ::Vanir::Exception(type, __PRETTY_FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__); \
    } catch(Exception const& e) { \
        \
    } \
}

#endif /* VANIR_ERROR_EXCEPTION_H. */
