#pragma once
#include "vec.h"

namespace ray_tracing
{
    struct ray
    {
        vec3 start_point;
        vec3 direction;

    public:
        ray() = default;
        ray(const vec3 &p_start, const vec3 &direction_) : start_point(p_start), direction(direction_) {}

        vec3 point_at_parameter(float t) const { return start_point + t * direction; }
    };

}