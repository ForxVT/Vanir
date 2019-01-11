#include <Vanir/MathsUtils.h>
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
        return radiant * (180.0f / VANIR_MATHS_PIF);
    }

    double MathsUtils::ToDegree(const double radiant)
    {
        return radiant * (180.0 / VANIR_MATHS_PID);
    }

    float MathsUtils::ToRadiant(const float degree)
    {
        return degree * (VANIR_MATHS_PIF / 180.0f);
    }

    double MathsUtils::ToRadiant(const double degree)
    {
        return degree * (VANIR_MATHS_PID / 180.0);
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