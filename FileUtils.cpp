#include <Vanir/FileUtils.h>
#include <Vanir/StringUtils.h>
#include <fstream>
#include <sstream>
// FIXME: FILESYSTEM - https://sourceforge.net/p/mingw-w64/bugs/737/
#ifdef PLATFORM_WINDOWS
#include <direct.h>
#elif PLATFORM_LINUX
#include <experimental/filesystem>
#include <unistd.h>
#include <cstring>
#else
#include <unistd.h>
#include <sys/stat.h>
#endif
#include <stdio.h>
#include <iostream>
#include "FileUtils.h"


namespace Vanir
{
    bool FileUtils::FileExist(const std::string& path)
    {
        std::ifstream file(path);

        return file.good();
    }

    bool FileUtils::FolderExist(const std::string& path)
    {
#ifdef PLATFORM_WINDOWS
        DWORD ftyp = ::GetFileAttributesA(path.c_str());

        if (ftyp == INVALID_FILE_ATTRIBUTES)
            return false;

        if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
            return true;

        return false;
#elif PLATFORM_LINUX
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
#ifdef PLATFORM_WINDOWS
        ::CreateDirectoryA(path.c_str(), NULL);
#elif PLATFORM_LINUX
        std::experimental::filesystem::create_directory(path);
#else
      mkdir(path.c_str(), 0755);
#endif
    }

    void FileUtils::AddFile(const std::string& path, const std::string& text)
    {
        if (!Vanir::FileUtils::FolderExist(Vanir::FileUtils::GetDirectoryPathFromFilePath(path)))
            Vanir::FileUtils::AddFolder(Vanir::FileUtils::GetDirectoryPathFromFilePath(path));

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

#ifdef PLATFORM_WINDOWS
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
