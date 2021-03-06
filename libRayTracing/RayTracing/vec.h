#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <cmath>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>

namespace ray_tracing
{
    using glm::cross;
    using glm::dot;
    using glm::mat3;
    using glm::mat4; // column major
    using glm::uvec2;
    using glm::uvec3;
    using glm::vec2;
    using glm::vec3;
    using glm::vec4;

    inline std::ostream &operator<<(std::ostream &os, const vec3 &v)
    {
        return (os << glm::to_string(v));
    }

    inline vec3 operator*(double a, const vec3 &v) { return float(a) * v; }
    inline vec3 operator*(const vec3 &v, double a) { return float(a) * v; }
    inline vec3 operator/(const vec3 &v, float a) { return vec3{v.x / a, v.y / a, v.z / a}; }

    inline float squared_length(const vec3 &a) { return glm::dot(a, a); }
    inline float length(const vec3 &a) { return std::sqrt(squared_length(a)); }
    inline vec3 unit_vector(const vec3 &a) { return a / length(a); }
    inline vec3 reflect(const vec3 &v, const vec3 &n) { return v - 2 * dot(v, n) * n; }
    vec3 refract(const vec3 &v, const vec3 &n, float ni_over_nt);
    vec3 refract(const vec3 &v, const vec3 &n, float ni_over_nt, bool &is_total_reflection);

    template <typename T>
    inline T clamp(T value, T min, T max) { return std::max(std::min(value, max), min); }

    extern const float DEGREE;
    inline float radian_to_degree(float radians) { return radians / DEGREE; }
    inline float degree_to_radian(float degrees) { return degrees * DEGREE; }

    inline float fractional_part(float x) { return x > 0 ? x - std::floor(x) : x - std::ceil(x); }
}