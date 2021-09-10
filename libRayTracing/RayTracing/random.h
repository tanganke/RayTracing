#pragma once
#include "vec.h"
#include <stdlib.h>

namespace ray_tracing
{
    template <typename T>
    inline T random();
    template <>
    inline float random<float>() { return float(drand48()); }
    template <>
    inline double random<double>() { return drand48(); }

    template <typename T>
    inline T random(T min_, T max_) { return min_ + random<T>(max_ - min_); }

    inline vec3 random_vec3() { return vec3(random<float>(), random<float>(), random<float>()); }
    inline vec3 random_vec3(float min_, float max_) { return min_ + random_vec3() * (max_ - min_); }

    vec3 random_vec3_in_unit_sphere();
}