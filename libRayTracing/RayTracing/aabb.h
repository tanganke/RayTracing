#pragma once
#include "ray.h"
#include "float.h"
#include <iostream>

namespace ray_tracing
{
    class aabb
    {
    public:
        vec3 lower_bound, higher_bound;

    public:
        aabb() : lower_bound{FLT_MAX, FLT_MAX, FLT_MAX}, higher_bound{FLT_MIN, FLT_MIN, FLT_MIN} {};
        aabb(const vec3 &lower_bound_, const vec3 &higher_bound_) : lower_bound{lower_bound_}, higher_bound{higher_bound_} {}
        aabb(const aabb &a, const aabb &b)
        {
            vec3 lower{std::min(a.lower_bound[0], b.lower_bound[0]), std::min(a.lower_bound[1], b.lower_bound[1]), std::min(a.lower_bound[2], b.lower_bound[2])};
            vec3 higher{std::max(a.higher_bound[0], b.higher_bound[0]), std::max(a.higher_bound[1], b.higher_bound[1]), std::max(a.higher_bound[2], b.higher_bound[2])};
            lower_bound = lower;
            higher_bound = higher;
        }

        bool hit(const ray &r, float t_min, float t_max) const
        {
            for (int i = 0; i < 3; ++i)
            {
                float t[2] = {(lower_bound[i] - r.start_point[i]) / r.direction[i],
                              (higher_bound[i] - r.start_point[i]) / r.direction[i]};
                float interval[2] = {std::min(t[0], t[1]), std::max(t[0], t[1])};
                t_min = std::max(interval[0], t_min);
                t_max = std::min(interval[1], t_max);
                if (t_max <= t_min)
                    return false;
            }
            return true;
        }

        inline void clear()
        {
            *this = aabb();
        }
    };

    inline std::ostream &operator<<(std::ostream &os, const aabb &bbox)
    {
        os << "aabb(" << bbox.lower_bound << ',' << bbox.higher_bound << ')';
        return os;
    }
}