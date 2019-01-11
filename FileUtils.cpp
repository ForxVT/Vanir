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
#define AlphabeticSorting alphasort
#else
#include <unistd.h>
#include <sys/stat.h>
#define AlphabeticSorting alphasort
#endif
#include <Vanir/Utils/Dirent/Dirent.h>
#include <stdio.h>
#include <iostream>

namespace Vanir
{
    FileUtils::FileUtils()
    {

    }

    FileUtils::~FileUtils()
    {

    }

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

    std::string FileUtils::GetExtension(const std::string& name)
    {
        const auto loc = name.find_last_of('.');

        if (loc != std::string::npos)
            return name.substr(loc + 1, std::string::npos);

        return "";
    }

    std::string FileUtils::GetWithoutExtension(const std::string& name)
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

    std::vector<File> FileUtils::ScanDirectory(const std::string& path)
    {
        struct dirent ** files = nullptr;
        const auto numberOfFiles = scandir(path.c_str(), &files, nullptr, AlphabeticSorting);
        auto fileList = std::vector<File>();

        if (numberOfFiles >= 0)
        {
            for (auto i = 0; i < numberOfFiles; i++)
            {
                const auto ent = files[i];
                File infos;

                infos.Name = ent->d_name;

                if (infos.Name != ".")
                {
                    switch (ent->d_type)
                    {
                        case DT_REG:
                            infos.Type = 'F';
                            break;
                        case DT_DIR:
                            infos.Type = 'D';
                            break;
                        case DT_LNK:
                            infos.Type = 'L';
                            break;
                        default:
                            infos.Type = 'E';
                            break;
                    }

                    fileList.emplace_back(infos);
                }
            }

            for (auto i = 0; i < numberOfFiles; i++)
                free(files[i]);

            free(files);
        }

        return fileList;
    }

#ifdef PLATFORM_WINDOWS
    int FileUtils::AlphabeticSorting(const void* a, const void* b)
    {
        return strcoll(((dirent*)a)->d_name, ((dirent*)b)->d_name);
    }
#endif

    bool FileUtils::StringEndsWith(const std::string& value, const std::string& ending)
    {
        if (ending.size() > value.size())
            return false;

        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }

} /* Namespace Vanir. */