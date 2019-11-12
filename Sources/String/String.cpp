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

#include <locale>
#include <codecvt>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <Vanir/String/String.h>
#include <Vanir/Math/Random.h>

namespace Vanir {
    bool String::StartsWith(const std::string& text,  const std::string& start) {
        return text.rfind(start, 0) == 0;
    }
    
    std::string String::GenerateUUID() {
#ifdef _WIN32
        UUID uuid;

        UuidCreate(&uuid);

        char *uuidStr;

        UuidToStringA(&uuid, (RPC_CSTR*)&uuidStr);
        std::string result(uuidStr);

        ToUppercase(result);

        RpcStringFreeA((RPC_CSTR*)&uuidStr);
#else
        srand(time(nullptr));

        char * buffer = new char[36];

        sprintf(buffer, "%x-%x-%x-%x-%x%x",
                rand(),
                rand() % 0x3fff + 0x8000,
                ((rand() & 0x0fff) | 0x4000),
                rand() % 0x3fff + 0x8000,
                rand(), rand() % 0x3fff + 0x8000);

        std::string result(buffer);

        String::ToUppercase(result);

        delete[] buffer;
#endif

        return result;
    }

    std::vector<std::string> String::SplitString(const std::string& text, const std::string& delimitation) {
        std::vector<std::string> result;
        std::string::size_type startPos = 0;
        std::string::size_type endPos;

        do {
            endPos = text.find_first_of(delimitation, startPos);
            const auto length = endPos - startPos;

            if (length != 0) {
                result.push_back(text.substr(startPos, length));
            }

            startPos = endPos + 1;
        } while (endPos != std::string::npos);

        return result;
    }

    std::vector<std::string> String::SplitString(const std::string& text, const char delimitation) {
        return SplitString(text, std::string(1, delimitation));
    }

    std::wstring String::StringToWString(const std::string& text) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

        return converter.from_bytes(text);
    }

    std::string String::WStringToString(const std::wstring& text) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

        return converter.to_bytes(text);
    }

#ifdef _WIN32
    std::wstring String::StringToBSTR(const std::string& text) {
        std::wstring ret;

        if (const auto cwch = MultiByteToWideChar(CP_ACP, 0, text.c_str(), -1, nullptr, 0)) {
            ret.resize(cwch - 1);

            if (!MultiByteToWideChar(CP_ACP, 0, text.c_str(), -1, &ret[0], static_cast<int>(ret.size())) &&
                ERROR_INSUFFICIENT_BUFFER == GetLastError()) {
                return ret;
            }
        }

        return ret;
    }

    std::string String::BSTRToString(BSTR text) {
        const auto src_len = SysStringLen(text);
        std::string ret;

        if (const auto len = WideCharToMultiByte(CP_ACP, 0, text, src_len + 1, nullptr, 0, nullptr, nullptr)) {
            ret.resize(len + 1, '\0');

            if (!WideCharToMultiByte(CP_ACP, 0, text, src_len + 1, &ret[0], len, nullptr, nullptr))
                ret.clear();
        }
        return ret;
    }
#endif

    void String::ReverseString(std::string& text) {
        const auto textLength = text.length();

        for (auto i = 0; i < int(textLength) / 2; i++)
            std::swap(text[i], text[textLength - i - 1]);
    }

    void String::ReverseWString(std::wstring& text) {
        const auto textLength = text.length();

        for (auto i = 0; i < int(textLength) / 2; i++)
            std::swap(text[i], text[textLength - i - 1]);
    }

    std::string String::BoolToString(const bool value) {
        return value ? "true" : "false";
    }

    void String::ToUppercase(std::string &text) {
        std::transform(text.begin(), text.end(), text.begin(), ::toupper);
    }

    void String::ToLowercase(std::string &text) {
        std::transform(text.begin(), text.end(), text.begin(), ::tolower);
    }

    bool String::StringEndsWith(const std::string& value, const std::string& ending) {
        if (ending.size() > value.size())
            return false;

        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }

} /* Namespace Vanir. */
