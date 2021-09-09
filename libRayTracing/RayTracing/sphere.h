#pragma once
#include "material.h"
#include <memory>

namespace ray_tracing
{
    int ray_sphere_hit_test(const ray &r, const sphere &sphere);

    class sphere : public hitable
    {
    public:
        vec3 center;
        float radius;
        std::shared_ptr<material> mat;

        sphere(vec3 center_, float radius_) : center(center_), radius(radius_) {}
        sphere(vec3 center_, float radius_, std::shared_ptr<material> material_) : sphere(center_, radius_)
        {
            mat = material_;
        }

        virtual bool hit(const ray &ray, float t_min, float t_max, hit_record &out_record) const override
        {
        }
    };

}