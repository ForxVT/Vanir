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

#include <Vanir/Maths/MathsUtils.h>
#include <math.h>

namespace Vanir
{
    bool MathsUtils::IsOdd(const int number)
    {
        return number % 2 != 0;
    }

    bool MathsUtils::IsEven(const int number)
    {
        return number % 2 == 0;
    }

    float MathsUtils::ToDegree(const float radiant)
    {
        return radiant * (180.0f / VANIR_MATHS_PI_F);
    }

    double MathsUtils::ToDegree(const double radiant)
    {
        return radiant * (180.0 / VANIR_MATHS_PI_D);
    }

    float MathsUtils::ToRadiant(const float degree)
    {
        return degree * (VANIR_MATHS_PI_F / 180.0f);
    }

    double MathsUtils::ToRadiant(const double degree)
    {
        return degree * (VANIR_MATHS_PI_D / 180.0);
    }

    float MathsUtils::Lerp(const float value1, const float value2, const float alpha)
    {
        return (1.0f - alpha) * value1 + alpha * value2;
    }

    double MathsUtils::Lerp(const double value1, const double value2, const double alpha)
    {
        return (1.0f - alpha) * value1 + alpha * value2;
    }

    void MathsUtils::Rotate(float* x, float* y, float& originX, float& originY, float& angle)
    {
        const auto radiantAngle = ToRadiant(angle);
        const auto s = sin(radiantAngle);
        const auto c = cos(radiantAngle);

        *x -= originX;
        *y -= originY;

        const auto xnew = *x * c - *y * s;
        const auto ynew = *x * s + *y * c;

        *x = xnew + originX;
        *y = ynew + originY;
    }

    void MathsUtils::Rotate(double* x, double* y, double& originX, double& originY, double& angle)
    {
        const auto radiantAngle = ToRadiant(angle);
        const auto s = sin(radiantAngle);
        const auto c = cos(radiantAngle);

        *x -= originX;
        *y -= originY;

        const auto xnew = *x * c - *y * s;
        const auto ynew = *x * s + *y * c;

        *x = xnew + originX;
        *y = ynew + originY;
    }

} /* Namespace Vanir. */
