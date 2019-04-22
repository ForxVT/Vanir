//==================================================================================//
//                                                                                  //
//  Copyright (c) 2019 Hugo Kindel <kindelhugo@gmail.com>                           //
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

#ifndef VANIR_MATHS_MATHSUTILS_H
#define VANIR_MATHS_MATHSUTILS_H

#include <Vanir/Common.h>

#define VANIR_MATHS_PI_D 3.14159265
#define VANIR_MATHS_PI_F 3.14159265f

namespace Vanir
{
    // TODO: VANIR: MATHS: Add a random system (with seed support).
    class MathsUtils
    {
    public:
        static bool IsOdd(int number);
        static bool IsEven(int number);
        static float ToDegree(float radiant);
        static double ToDegree(double radiant);
        static float ToRadiant(float degree);
        static double ToRadiant(double degree);
        static float Lerp(float value1, float value2, float alpha);
        static double Lerp(double value1, double value2, double alpha);
        static void Rotate(float* x, float* y, float& originX, float& originY, float& angle);
        static void Rotate(double* x, double* y, double& originX, double& originY, double& angle);
    };

} /* Namespace Vanir. */

#endif /* VANIR_MATHS_MATHSUTILS_H. */
