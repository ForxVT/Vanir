// TODO: Random system
#ifndef VANIR_MATHSUTILS_H
#define VANIR_MATHSUTILS_H

#define VANIR_MATHS_PID 3.141592
#define VANIR_MATHS_PIF 3.141592f

namespace Vanir
{
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

#endif /* VANIR_MATHSUTILS_H. */