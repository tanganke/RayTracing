#pragma once
#include "material.h"
#include <memory>

namespace ray_tracing
{
    class sphere : public hittable
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

        virtual bool hit(const ray &r, float t_min, float t_max, hit_record &out_record) const override
        {
            vec3 oc = r.origin() - center;
            float a = dot(r.direction, r.direction);
            float b = 2 * dot(oc, r.direction);
            float c = dot(oc, oc) - radius * radius;
            float discriminant = b * b - 4 * a * c;
            if (discriminant > 0)
            {
                float temp;
                temp = (-b - std::sqrt(discriminant)) / (2 * a);
                if (temp < t_max && temp > t_min)
                {
                    out_record.ray_parameter = temp;
                    out_record.position = r.point_at_parameter(temp);
                    out_record.normal = (out_record.position - center) / radius;
                    out_record.mat_ptr = mat.get();
                    out_record.front_face = true;
                    return true;
                }
                temp = (-b + sqrt(discriminant)) / (2 * a);
                if (temp < t_max && temp > t_min)
                {
                    out_record.ray_parameter = temp;
                    out_record.position = r.point_at_parameter(temp);
                    out_record.normal = (out_record.position - center) / radius;
                    out_record.front_face = false;
                    out_record.mat_ptr = mat.get();
                    return true;
                }
            }
            return false;
        }
    };

}