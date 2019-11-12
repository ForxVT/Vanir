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

#ifndef VANIR_FILESYSTEM_FILESYSTEM_H
#define VANIR_FILESYSTEM_FILESYSTEM_H

#include <Vanir/Common.h>

namespace Vanir {
    /// Class containing various file utility methods.
    class FileSystem {
    public:
        /// Get the root directory of the executable where this was used.
        static std::string GetRootDirectory();
        /// Return the extension of a path.
        static std::string GetExtensionFromFilePath(const std::string& path);
        /// Return the directory path from a file path.
        static std::string GetDirectoryPathFromFilePath(const std::string& path);
        /// Return a path without his extension (if he has one).
        static std::string GetPathWithoutExtension(const std::string& name);
        /// Return if a folder exist.
        static bool DirectoryExist(const std::string& path);
        /// Return if a file exist.
        static bool FileExist(const std::string& path);
        /// Create a new folder.
        static void AddDirectory(const std::string &path);
        /// Create a new file.
        static void AddFile(const std::string& path, const std::string& text = "");
        /// Create a new file with multiples lines.
        static void AddFile(const std::string& path, std::vector<std::string> text);
        /// Return the content of a file.
        static std::string ReadFileToMemory(const std::string& path);
    };

} /* Namespace Vanir. */

#endif /* VANIR_FILESYSTEM_FILESYSTEM_H. */
