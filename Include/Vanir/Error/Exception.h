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

#ifndef VANIR_EXCEPTION_H
#define VANIR_EXCEPTION_H

#include <Vanir/Common.h>
#include <Vanir/Logger/Logger.h>

namespace Vanir
{
    class VANIR_EXPORT Exception : public std::exception
    {
    public:
        Exception(const std::string &type, const std::string &message, const std::string &source, const std::string &file, int line);
        Exception(const Exception& rhs);
        ~Exception() noexcept = default;

        virtual const std::string& GetDescription() const;

        const char* what() const noexcept override;

    protected:
        mutable std::string m_error;
        std::string m_type;
        std::string m_message;
        std::string m_source;
        std::string m_file;
        int m_line;
    };

} /* Namespace Vanir. */

#define THROW_EXCEPTION(type, message) \
ULOG_ERROR("EXCEPTION - ", type, ": ", message); \
throw ::Vanir::Exception(type, message, __PRETTY_FUNCTION__, __FILE__, __LINE__)

#endif /* VANIR_EXCEPTION_H. */
