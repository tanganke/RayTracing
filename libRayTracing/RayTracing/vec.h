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
    using glm::mat4;
    using glm::vec3;
    using glm::vec4;

    inline std::ostream &operator<<(std::ostream &os, const vec3 &v)
    {
        return (os << glm::to_string(v));
    }

    inline vec3 operator*(double a, const vec3 &v) { return float(a) * v; }
    inline vec3 operator*(const vec3 &v, double a) { return float(a) * v; }

    inline float squared_length(const vec3 &a) { return glm::dot(a, a); }
    inline float length(const vec3 &a) { return std::sqrt(squared_length(a)); }
    inline vec3 unit_vector(const vec3 &a) { return a / length(a); }
    inline vec3 reflect(const vec3 &v, const vec3 &n) { return v - 2 * dot(v, n) * n; }
    vec3 refract(const vec3 &v, const vec3 &n, float ni_over_nt);
    vec3 refract(const vec3 &v, const vec3 &n, float ni_over_nt, bool &is_total_reflection);

    inline float clamp(float value, float min, float max) { return std::max(std::min(value, max), min); }
}