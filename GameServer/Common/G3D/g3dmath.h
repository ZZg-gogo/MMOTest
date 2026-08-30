#ifndef __G3D_MATH_H__
#define __G3D_MATH_H__

#include <cmath>
#include <limits>

constexpr double FuzzyEpsilon64 = 0.0000005;
constexpr float  FuzzyEpsilon32 = 0.00001f;

inline double eps(double a, double b)
{
    (void)b;

    const double aa = std::abs(a) + 1.0;
    
    if (std::isinf(aa))
    {
        return FuzzyEpsilon64;
    }

    return FuzzyEpsilon64 * aa;
}

inline float eps(float a, float b)
{
    (void)b;

    const float aa = std::abs(a) + 1.0f;

    if (std::isinf(aa))
    {
        return FuzzyEpsilon32;
    }

    return FuzzyEpsilon32 * aa;
}

inline bool fuzzyEq(double a, double b)
{
    return a == b || std::abs(a - b) <= eps(a, b);
}

inline bool fuzzyEq(float a, float b)
{
    return a == b || std::abs(a - b) <= eps(a, b);
}

inline bool fuzzyNotEq(double a, double b)
{
    return !fuzzyEq(a, b);
}

inline bool fuzzyNotEq(float a, float b)
{
    return !fuzzyEq(a, b);
}



#endif