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

#ifndef VANIR_STRING_STRING_H
#define VANIR_STRING_STRING_H

#include <iomanip>
#include <sstream>
#ifdef _WIN32
#include <combaseapi.h>
#endif
#include <Vanir/Common.h>

namespace Vanir {
    /// Class containing various string utility methods.
    class String {
    public:
        /// Generate an UUID.
        static std::string generateUUID();
        /// Convert an integer to his hexadecimal representation.
        template< typename T >
        static std::string integerToHexadecimal(T integer, bool showFullLength = false);
        /// Split a string in a vector of string by a string delimiter.
        static std::vector<std::string> split(const std::string& text, const std::string& delimitation);
        /// Split a string in a vector of string by a char delimiter.
        static std::vector<std::string> split(const std::string& text, char delimitation);
        /// Convert a string to a wide-string.
        static std::wstring stringToWString(const std::string& text);
        /// Convert a wide-string to a string?
        static std::string wstringToString(const std::wstring& text);
#ifdef _WIN32
        /// Convert a string to a BSTR.
        static std::wstring stringToBSTR(const std::string& text);
        /// Convert a BSTR to a string.
        static std::string bstrToString(BSTR text);
#endif
        /// Reverse the text order of a string.
        static void reverseString(std::string& text);
        /// Reverse the text order of a wide-string.
        static void reverseWString(std::wstring& text);
        /// Convert a boolean to a string.
        static std::string boolToString(bool value);
        /// Convert a string to uppercase.
        static void toUppercase(std::string& text);
        /// Convert a string to lowercase.
        static void toLowercase(std::string& text);
        /// Return if a string starts with a specific string.
        static bool startsWith(const std::string& text, const std::string& start);
        /// Return if a value string ends with a specific string.
        static bool endsWith(const std::string& value, const std::string& ending);
        /// Implementation of a Levenshtein distance algorithm.
        /// Source from: https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C++
        template<typename T>
        constexpr static unsigned int calculateLevenshteinDistance(
                const T &source,
                const T &target,
                typename T::size_type insert_cost = 1,
                typename T::size_type delete_cost = 1,
                typename T::size_type replace_cost = 1) {
            if (source.size() > target.size())
                return calculateLevenshteinDistance(target, source, delete_cost, insert_cost, replace_cost);

            using TSizeType = typename T::size_type;
            const TSizeType min_size = source.size(), max_size = target.size();
            std::vector<TSizeType> lev_dist(min_size + 1);
            lev_dist[0] = 0;

            for (TSizeType i = 1; i <= min_size; ++i)
                lev_dist[i] = lev_dist[i - 1] + delete_cost;

            for (TSizeType j = 1; j <= max_size; ++j) {
                TSizeType previous_diagonal = lev_dist[0], previous_diagonal_save;
                lev_dist[0] += insert_cost;

                for (TSizeType i = 1; i <= min_size; ++i) {
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

    template< typename T >
    std::string String::integerToHexadecimal(T integer, bool showFullLength) {
        std::stringstream stream;

        if (showFullLength)
            stream << std::setfill ('0') << std::setw(sizeof(T) * 2) << std::hex << integer;
        else
            stream << std::hex << integer;

        return stream.str();
    }

} /* Namespace Vanir. */

#endif /* VANIR_STRING_STRING_H. */
