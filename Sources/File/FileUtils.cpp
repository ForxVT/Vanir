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

#include <Vanir/File/FileUtils.h>
#include <Vanir/String/StringUtils.h>
#include <fstream>
#include <sstream>
// TODO: VANIR: FILE: Remove workaround when bug fixed: https://sourceforge.net/p/mingw-w64/bugs/737/
#ifdef _WIN32
#include <direct.h>
#elif __unix__
#include <experimental/filesystem>
#include <unistd.h>
#include <cstring>
#else
#include <unistd.h>
#include <sys/stat.h>
#endif
#include <stdio.h>
#include <iostream>

namespace Vanir
{
    bool FileUtils::FileExist(const std::string& path)
    {
        std::ifstream file(path);

        return file.good();
    }

    bool FileUtils::FolderExist(const std::string& path)
    {
#ifdef _WIN32
        DWORD ftyp = ::GetFileAttributesA(path.c_str());

        if (ftyp == INVALID_FILE_ATTRIBUTES)
            return false;

        if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
            return true;

        return false;
#elif __unix__
        return std::experimental::filesystem::exists(path);
#else
        struct stat statbuf;

        if (stat(path.c_str(), &statbuf) != -1)
        {
            if (S_ISDIR(statbuf.st_mode))
                return true;
        }

        return false;
#endif
    }

    std::string FileUtils::GetFilePathExtension(const std::string& name)
    {
        const auto loc = name.find_last_of('.');

        if (loc != std::string::npos)
            return name.substr(loc + 1, std::string::npos);

        return "";
    }

    std::string FileUtils::GetFilePathWithoutExtension(const std::string& name)
    {
        const auto loc = name.find_last_of('.');

        if (loc != std::string::npos)
            return name.substr(0, loc);

        return name;
    }

    void FileUtils::AddFolder(const std::string& path)
    {
#ifdef _WIN32
        ::CreateDirectoryA(path.c_str(), NULL);
#elif __unix__
        std::experimental::filesystem::create_directory(path);
#else
      mkdir(path.c_str(), 0755);
#endif
    }

    void FileUtils::AddFile(const std::string& path, const std::string& text)
    {
        auto dir = Vanir::FileUtils::GetDirectoryPathFromFilePath(path);

        if (!dir.empty())
        {
            if (!Vanir::FileUtils::FolderExist(dir))
                Vanir::FileUtils::AddFolder(dir);
        }

        std::ofstream fs;

        fs.open(path, std::ios::out);
        fs << text;
        fs.close();
    }

    void FileUtils::AddFile(const std::string& path, std::vector<std::string> text)
    {
        std::ofstream fs;

        fs.open(path, std::ios::out);

        for (auto& i : text)
        {
            if (!i.empty())
                fs << i << "\n";
        }

        fs.close();
    }

    std::string FileUtils::ReadFile(const std::string& path)
    {
        std::stringstream fileStream;
        std::ifstream file(path);

        fileStream << file.rdbuf();
        file.close();

        return fileStream.str();
    }

    std::string FileUtils::GetRootDirectory()
    {
        char buff[FILENAME_MAX];

#ifdef _WIN32
        _getcwd(buff, FILENAME_MAX);
#else
        getcwd(buff, FILENAME_MAX);
#endif

        std::string current_working_dir(buff);

        return current_working_dir;
    }

    std::string FileUtils::GetDirectoryPathFromFilePath(const std::string &path)
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

} /* Namespace Vanir. */
