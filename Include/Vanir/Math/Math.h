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

#ifndef VANIR_MAHT_MATH_H
#define VANIR_MAHT_MATH_H

#include <Vanir/Common.h>

namespace Vanir {
    /// Class containing various mathematic utility methods.
    class Math {
    public:
        /// Return if a given integer is odd.
        static bool IsOdd(int32_t number);
        /// Return if a given integer is even.
        static bool IsEven(int32_t number);
        /// Return a converted float from radiant to degree.
        static float ToDegree(float radiant);
        /// Return a converted float from degree to radiant.
        static float ToRadiant(float degree);
        /// Return the interpolation of two values by an alpha (0 meaning value A, 1 meaning value B).
        static float Lerp(float alpha, float a, float b);
        /// Return a divided number rounded up (only working on positive numbers).
        template<class T>
        static constexpr T DivideAndRoundUp(T n, T d) {
            return (n + d - 1) / d;
        }

        /// Constant for PI.
        static constexpr float PI = 3.14159265358979323846f;
        /// Constant to help converting radiant to degree.
        static constexpr float RAD2DEG = 180.0f / PI;
        /// Constant to help converting degree to radiant.
        static constexpr float DEG2RAD = PI / 180.0f;
    };

} /* Namespace Vanir. */

#endif /* VANIR_MAHT_MATH_H. */
