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

#include <Vanir/FileSystem/FileSystem.h>
#include <Vanir/String/String.h>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iostream>
#ifdef _WIN32
// TODO: VANIR: FILE: Remove workaround when bug fixed: https://sourceforge.net/p/mingw-w64/bugs/737/
#include <direct.h>
#elif defined(__unix__)
#include <experimental/filesystem>
#include <zconf.h>
#endif

namespace Vanir
{
    std::string FileSystem::GetRootDirectory()
    {
        char buff[FILENAME_MAX];

#ifdef _WIN32
        _getcwd(buff, FILENAME_MAX);
#else
        getcwd(buff, FILENAME_MAX);
#endif

        std::string currentWorkingDirectory(buff);

        return currentWorkingDirectory;
    }

    std::string FileSystem::GetExtensionFromFilePath(const std::string &name)
    {
        const auto loc = name.find_last_of('.');

        if (loc != std::string::npos)
            return name.substr(loc + 1, std::string::npos);

        return std::string();
    }

    std::string FileSystem::GetDirectoryPathFromFilePath(const std::string &path)
    {
        std::string directoryPath = std::string();
        std::string separator = "\\";

        if (path.find(separator) == std::string::npos)
            separator = "/";

        const size_t i = path.rfind(separator);

        if (i != std::string::npos)
            directoryPath = path.substr(0, i);

        return directoryPath;
    }

    std::string FileSystem::GetPathWithoutExtension(const std::string &name)
    {
        const auto loc = name.find_last_of('.');

        if (loc != std::string::npos)
            return name.substr(0, loc);

        return name;
    }

    bool FileSystem::DirectoryExist(const std::string &path)
    {
#ifdef _WIN32
        DWORD fileAttributes = ::GetFileAttributesA(path.c_str());

        return (fileAttributes != INVALID_FILE_ATTRIBUTES && fileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
#elif __unix__
        return std::experimental::filesystem::exists(path);
#endif
    }

    bool FileSystem::FileExist(const std::string &path)
    {
        std::ifstream file(path);

        return file.good();
    }

    void FileSystem::AddDirectory(const std::string &path)
    {
#ifdef _WIN32
        ::CreateDirectoryA(path.c_str(), nullptr);
#elif __unix__
        std::experimental::filesystem::create_directory(path);
#endif
    }

    void FileSystem::AddFile(const std::string &path, const std::string &text)
    {
        auto dir = Vanir::FileSystem::GetDirectoryPathFromFilePath(path);

        if (!dir.empty())
        {
            if (!Vanir::FileSystem::DirectoryExist(dir))
                Vanir::FileSystem::AddDirectory(dir);
        }

        std::ofstream fs(path, std::ios::out);

        fs << text;

        fs.close();
    }

    void FileSystem::AddFile(const std::string &path, std::vector<std::string> text)
    {
        auto dir = Vanir::FileSystem::GetDirectoryPathFromFilePath(path);
    
        if (!dir.empty())
        {
            if (!Vanir::FileSystem::DirectoryExist(dir))
                Vanir::FileSystem::AddDirectory(dir);
        }
        
        std::ofstream fs(path, std::ios::out);

        for (auto& i : text)
        {
            if (!i.empty())
                fs << i << "\n";
        }

        fs.close();
    }

    std::string FileSystem::ReadFileToMemory(const std::string &path)
    {
        auto close_file = [](FILE* f) { fclose(f); };
    
        auto holder = std::unique_ptr<FILE, decltype(close_file)>(fopen(path.c_str(), "rb"), close_file);
        if (!holder)
            return "";
    
        FILE* f = holder.get();
    
        if (fseek(f, 0, SEEK_END) < 0)
            return "";
    
        const long size = ftell(f);
        if (size < 0)
            return "";
    
        if (fseek(f, 0, SEEK_SET) < 0)
            return "";
    
        std::string res;
        res.resize(size);
    
        fread(const_cast<char*>(res.data()), 1, size, f);
    
        return res;
    }

} /* Namespace Vanir. */
