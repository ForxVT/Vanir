#include <Vanir/StringUtils.h>
#include <Vanir/Logger.h>
#include <locale>
#include <codecvt>
#include <sstream>
#include <iomanip>
#include <algorithm>

namespace Vanir
{
    std::vector<std::string> StringUtils::SplitString(const std::string& text, const std::string& delimitation)
    {
        std::vector<std::string> result;
        std::string::size_type startPos = 0;
        std::string::size_type endPos;

        do
        {
            endPos = text.find_first_of(delimitation, startPos);
            const auto length = endPos - startPos;

            if (length != 0)
                result.push_back(text.substr(startPos, length));

            startPos = endPos + 1;
        } while (endPos != std::string::npos);

        return result;
    }

    std::vector<std::string> StringUtils::SplitString(const std::string& text, const char delimitation)
    {
        return SplitString(text, std::string(1, delimitation));
    }

    std::wstring StringUtils::StringToWString(const std::string& text)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

        return converter.from_bytes(text);
    }

    std::string StringUtils::WStringToString(const std::wstring& text)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

        return converter.to_bytes(text);
    }

#ifdef PLATFORM_WINDOWS
    std::wstring StringUtils::StringToBSTR(const std::string& text)
    {
        std::wstring ret;

        if (const auto cwch = MultiByteToWideChar(CP_ACP, 0, text.c_str(), -1, nullptr, 0))
        {
            ret.resize(cwch - 1);

            if (!MultiByteToWideChar(CP_ACP, 0, text.c_str(), -1, &ret[0], static_cast<int>(ret.size())))
                if (ERROR_INSUFFICIENT_BUFFER == GetLastError())
                    return ret;
        }

        return ret;
    }

    std::string StringUtils::BSTRToString(BSTR text)
    {
        const auto src_len = SysStringLen(text);
        std::string ret;

        if (const auto len = WideCharToMultiByte(CP_ACP, 0, text, src_len + 1, nullptr, 0, nullptr, nullptr))
        {
            ret.resize(len + 1, '\0');

            if (!WideCharToMultiByte(CP_ACP, 0, text, src_len + 1, &ret[0], len, nullptr, nullptr))
                ret.clear();
        }
        return ret;
    }
#endif

    void StringUtils::ReverseString(std::string& text)
    {
        const auto textLength = text.length();

        for (auto i = 0; i < int(textLength) / 2; i++)
            std::swap(text[i], text[textLength - i - 1]);
    }

    void StringUtils::ReverseWString(std::wstring& text)
    {
        const auto textLength = text.length();

        for (auto i = 0; i < int(textLength) / 2; i++)
            std::swap(text[i], text[textLength - i - 1]);
    }

    std::string StringUtils::BoolToString(const bool value)
    {
        return value ? "true" : "false";
    }

    void StringUtils::ToUppercase(std::string &text)
    {
        std::transform(text.begin(), text.end(), text.begin(), ::toupper);
    }

    void StringUtils::ToLowercase(std::string &text)
    {
        std::transform(text.begin(), text.end(), text.begin(), ::tolower);
    }

} /* Namespace Vanir. */