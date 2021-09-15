#pragma once
#include "hittable.h"

namespace ray_tracing
{
    class translate : public hittable
    {
    private:
        std::shared_ptr<hittable> obj_ptr;
        vec3 displacement;

    public:
        translate(std::shared_ptr<hittable> p, const vec3 &displacement_)
            : obj_ptr{p}, displacement{displacement_} {}

        virtual bool hit(const ray &r, float t_min, float t_max, hit_record &out_record) const override
        {
            ray moved_ray{r.origin() - displacement, r.direction};
            if (obj_ptr->hit(moved_ray, t_min, t_max, out_record))
            {
                out_record.position += displacement;
                return true;
            }
            else
                return false;
        }

        virtual bool bounding_box(aabb &out_aabb) const override
        {
            if (obj_ptr->bounding_box(out_aabb))
            {
                out_aabb.translate(displacement);
                return true;
            }
            else
                return false;
        }
    };
}