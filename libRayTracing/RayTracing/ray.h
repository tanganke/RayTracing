#pragma once
#include "vec.h"

namespace ray_tracing
{
    class ray
    {
    public:
        vec3 start_point;
        vec3 direction;

    public:
        ray() = default;
        ray(const vec3 &p_start, const vec3 &direction_) : start_point(p_start), direction(direction_) {}

        inline const vec3 &origin() const { return start_point; }
        inline vec3 unit_direction() const { return unit_vector(direction); }
        inline vec3 &make_unit_direction() { return (direction = unit_vector(direction)); }
        vec3 point_at_parameter(float t) const { return start_point + t * direction; }
    };

}