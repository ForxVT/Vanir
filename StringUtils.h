#ifndef VANIR_STRINGUTILS_H
#define VANIR_STRINGUTILS_H

#include <string>
#include <vector>
#ifdef PLATFORM_WINDOWS
#include <combaseapi.h>
#endif

namespace Vanir
{
    class StringUtils
    {
    public:
        static std::vector<std::string> SplitString(const std::string& text, const std::string& delimitation);
        static std::vector<std::string> SplitString(const std::string& text, char delimitation);
        static std::wstring StringToWString(const std::string& text);
        static std::string WStringToString(const std::wstring& text);
#ifdef PLATFORM_WINDOWS
        static std::wstring StringToBSTR(const std::string& text);
        static std::string BSTRToString(BSTR text);
#endif
        static void ReverseString(std::string& text);
        static void ReverseWString(std::wstring& text);
        static std::string BoolToString(bool value);
        static void ToUppercase(std::string& text);
        static void ToLowercase(std::string& text);
    };

} /* Namespace Vanir. */

#endif /* VANIR_STRINGUTILS_H. */
