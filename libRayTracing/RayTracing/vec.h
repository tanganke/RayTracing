#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

namespace ray_tracing
{
    using glm::mat3;
    using glm::mat4;
    using glm::vec3;
    using glm::vec4;

    inline float squared_length(const vec3 &a) { return glm::dot(a, a); }
    inline float length(const vec3 &a) { return std::sqrt(squared_length(a)); }
}