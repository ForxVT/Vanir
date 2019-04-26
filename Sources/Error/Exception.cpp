#include <utility>

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

#include <Vanir/Error/Exception.h>
#include <sstream>

namespace Vanir
{
    Exception::Exception(const std::string &type,
            const std::string &message, const std::string &source, const std::string &file, int line) :
            m_type(type), m_message(message), m_source(source), m_file(file), m_line(line)
    {

    }

    Exception::Exception(const Exception &rhs) :
            m_type(rhs.m_type), m_message(rhs.m_message), m_source(rhs.m_source), m_file(rhs.m_file), m_line(rhs.m_line)
    {

    }

    const std::string &Exception::GetDescription() const
    {
        if (m_error.empty())
        {
            std::stringstream error;

            error << "FATAL ERROR !\n\n";
            error << "Exception type: " << m_type << "\n";
            error << "Message: " << m_message << "\n";
            error << "In Method: " << m_source << "\n";

            if (m_line > 0)
                error << "In File: " << m_file << " (line " << m_line << ")";

            m_error = error.str();
        }

        return m_error;
    }

    const char *Exception::what() const noexcept
    {
        return GetDescription().c_str();
    }

} /* Namespace Vanir. */
