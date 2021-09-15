#pragma once
#include "hittable.h"
#include "rectangle.h"

namespace ray_tracing
{
    class axis_aligned_cuboid : public hittable_vector
    {
    private:
        vec3 lower_bound;
        vec3 higher_bound;
        std::shared_ptr<material> mat_ptr;

    public:
        axis_aligned_cuboid(const vec3 &p0, const vec3 &p1, std::shared_ptr<material> mat_ptr_) : mat_ptr{mat_ptr_}
        {
            for (int i = 0; i < 3; ++i)
            {
                lower_bound[i] = std::min(p0[i], p1[i]);
                higher_bound[i] = std::max(p0[i], p1[i]);
            }

            push_back(std::make_shared<xy_rect>(lower_bound.x, higher_bound.x, lower_bound.y, higher_bound.y, lower_bound.z, mat_ptr))
                .push_back(std::make_shared<xy_rect>(lower_bound.x, higher_bound.x, lower_bound.y, higher_bound.y, higher_bound.z, mat_ptr))
                .push_back(std::make_shared<yz_rect>(lower_bound.y, higher_bound.y, lower_bound.z, higher_bound.z, lower_bound.x, mat_ptr))
                .push_back(std::make_shared<yz_rect>(lower_bound.y, higher_bound.y, lower_bound.z, higher_bound.z, higher_bound.x, mat_ptr))
                .push_back(std::make_shared<zx_rect>(lower_bound.z, higher_bound.z, lower_bound.x, higher_bound.x, higher_bound.y, mat_ptr))
                .push_back(std::make_shared<zx_rect>(lower_bound.z, higher_bound.z, lower_bound.x, higher_bound.x, higher_bound.y, mat_ptr));
        }
    };
}