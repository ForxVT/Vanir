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

#ifdef VANIR_BUILD_JSON

#include <Vanir/JSON/JSONFile.h>
#include <Vanir/File/FileUtils.h>
#include <iomanip>
#include <fstream>

namespace Vanir
{
    void JSONFile::Load(const std::string &filepath)
    {
        m_filepath = filepath;

        if (!Vanir::FileUtils::FileExist(m_filepath))
            Vanir::FileUtils::AddFile(m_filepath, "{}\n");

        std::ifstream fileStream(m_filepath, std::ifstream::in);

        fileStream >> Content;

        fileStream.close();
    }

    void JSONFile::Save()
    {
        if (!m_filepath.empty())
        {
            std::ofstream fileStream(m_filepath, std::ofstream::trunc);

            fileStream << std::setw(4) << Content << std::endl;
            fileStream.close();

            Content.clear();
        }
    }

    const std::string &JSONFile::GetFilepath() const
    {
        return m_filepath;
    }


} /* Namespace Vanir. */

#endif