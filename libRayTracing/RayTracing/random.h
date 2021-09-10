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
    template <>
    inline int32_t random<int32_t>() { return random<double>() < 0.5 ? 0 : 1; }
    template <>
    inline int64_t random<int64_t>() { return random<double>() < 0.5 ? 0 : 1; }

    template <typename T>
    inline T random(T min_, T max_) { return min_ + random<T>() * (max_ - min_); }

    inline vec2 random_vec2() { return vec2{random<float>(), random<float>()}; }
    inline vec3 random_vec3() { return vec3(random<float>(), random<float>(), random<float>()); }

    template <>
    inline vec2 random<vec2>() { return random_vec2(); }
    template <>
    inline vec3 random<vec3>() { return random_vec3(); }

    inline vec2 random_vec2(float min_, float max_) { return min_ + random_vec2() * (max_ - min_); }
    inline vec3 random_vec3(float min_, float max_) { return min_ + random_vec3() * (max_ - min_); }

    vec2 random_vec2_in_unit_disk();
    vec3 random_vec3_in_unit_sphere();
}