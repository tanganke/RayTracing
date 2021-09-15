#pragma once
#include "hittable.h"

namespace ray_tracing
{
    class rotate_y : public hittable
    {
    private:
        std::shared_ptr<hittable> obj_ptr;
        float theta;

    public:
        rotate_y(std::shared_ptr<hittable> p, float theta_)
            : obj_ptr{p}, theta{theta_} {}

        virtual bool hit(const ray &r, float t_min, float t_max, hit_record &out_record) const override
        {
            vec3 origin = r.origin();
            vec3 direction = r.direction;
            origin[0] = std::cos(theta) * r.origin()[0] - std::sin(theta) * r.origin()[2];
            origin[2] = std::sin(theta) * r.origin()[0] + std::cos(theta) * r.origin()[2];
            direction[0] = std::cos(theta) * r.direction[0] - std::sin(theta) * r.direction[2];
            direction[2] = std::sin(theta) * r.direction[0] + std::cos(theta) * r.direction[2];
            ray rotated_r(origin, direction);
            if (obj_ptr->hit(rotated_r, t_min, t_max, out_record))
            {
                vec3 p = out_record.position;
                vec3 n = out_record.normal;
                p[0] = std::cos(theta) * out_record.position[0] + std::sin(theta) * out_record.position[2];
                p[2] = -std::sin(theta) * out_record.position[0] + std::cos(theta) * out_record.position[2];
                n[0] = std::cos(theta) * out_record.normal[0] + std::sin(theta) * out_record.normal[2];
                n[2] = -std::sin(theta) * out_record.normal[0] + std::cos(theta) * out_record.normal[2];
                out_record.position = p;
                out_record.normal = n;
                return true;
            }
            else
                return false;
        }

        virtual bool bounding_box(aabb &out_aabb) const override
        {
            aabb bbox;
            vec3 _min = bbox.lower_bound;
            vec3 _max = bbox.higher_bound;
            if (obj_ptr->bounding_box(bbox))
            {
                for (int i = 0; i < 2; i++)
                    for (int j = 0; j < 2; j++)
                        for (int k = 0; k < 2; k++)
                        {
                            float x = i * bbox.higher_bound.x + (1 - i) * bbox.lower_bound.x;
                            float y = j * bbox.higher_bound.y + (1 - j) * bbox.lower_bound.y;
                            float z = k * bbox.higher_bound.z + (1 - k) * bbox.lower_bound.z;
                            float new_x = std::cos(theta) * x + std::sin(theta) * z;
                            float new_z = -std::sin(theta) * x + std::cos(theta) * z;
                            vec3 tester{new_x, y, new_z};
                            for (int c = 0; c < 3; c++)
                            {
                                if (tester[c] > _max[c])
                                    _max[c] = tester[c];
                                if (tester[c] < _min[c])
                                    _min[c] = tester[c];
                            }
                        }
                out_aabb = aabb(_min, _max);
                return true;
            }
            else
                return false;
        }
    };

}