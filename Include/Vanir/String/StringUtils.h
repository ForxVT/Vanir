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

#ifndef VANIR_STRING_STRINGUTILS_H
#define VANIR_STRING_STRINGUTILS_H

#include <Vanir/Common.h>
#ifdef _WIN32
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
#ifdef _WIN32
        static std::wstring StringToBSTR(const std::string& text);
        static std::string BSTRToString(BSTR text);
#endif
        static void ReverseString(std::string& text);
        static void ReverseWString(std::wstring& text);
        static std::string BoolToString(bool value);
        static void ToUppercase(std::string& text);
        static void ToLowercase(std::string& text);
        static bool StringEndsWith(const std::string& value, const std::string& ending);
        // Source code from: https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C++
        template<typename T>
        static unsigned int GeneralizedLevensteinDistance(const T &source,
                                                          const T &target,
                                                          typename T::size_type insert_cost = 1,
                                                          typename T::size_type delete_cost = 1,
                                                          typename T::size_type replace_cost = 1)
        {
            if (source.size() > target.size())
                return GeneralizedLevensteinDistance(target, source, delete_cost, insert_cost, replace_cost);

            using TSizeType = typename T::size_type;
            const TSizeType min_size = source.size(), max_size = target.size();
            std::vector<TSizeType> lev_dist(min_size + 1);
            lev_dist[0] = 0;

            for (TSizeType i = 1; i <= min_size; ++i)
                lev_dist[i] = lev_dist[i - 1] + delete_cost;

            for (TSizeType j = 1; j <= max_size; ++j)
            {
                TSizeType previous_diagonal = lev_dist[0], previous_diagonal_save;
                lev_dist[0] += insert_cost;

                for (TSizeType i = 1; i <= min_size; ++i)
                {
                    previous_diagonal_save = lev_dist[i];

                    if (source[i - 1] == target[j - 1])
                        lev_dist[i] = previous_diagonal;
                    else
                        lev_dist[i] = std::min(std::min(lev_dist[i - 1] + delete_cost, lev_dist[i] + insert_cost), previous_diagonal + replace_cost);

                    previous_diagonal = previous_diagonal_save;
                }
            }

            return lev_dist[min_size];
        }
    };

} /* Namespace Vanir. */

#endif /* VANIR_STRING_STRINGUTILS_H. */