#ifndef VANIR_FILEUTILS_H
#define VANIR_FILEUTILS_H

#include <vector>
#include <Vanir/File.h>

namespace Vanir
{
    class FileUtils
    {
    public:
        FileUtils();
        ~FileUtils();

        static bool FileExist(const std::string& path);
        static bool FolderExist(const std::string& path);
        static std::string GetExtension(const std::string& name);
        static std::string GetWithoutExtension(const std::string& name);
        static void AddFolder(const std::string& path);
        static void AddFile(const std::string& path, const std::string& text = "");
        static void AddFile(const std::string& path, std::vector<std::string> text);
        static std::string ReadFile(const std::string& path);
        static std::string GetRootDirectory();
        static std::vector<File> ScanDirectory(const std::string& path = ".");
#ifdef PLATFORM_WINDOWS
        static int AlphabeticSorting(const void *a, const void *b);
#endif
        static bool StringEndsWith(const std::string& value, const std::string& ending);
    };

} /* Namespace Vanir. */

#endif /* VANIR_FILEUTILS_H. */