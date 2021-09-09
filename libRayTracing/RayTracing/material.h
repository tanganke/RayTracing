#pragma once
#include "ray.h"
#include "hitable.h"
#include "random.h"

namespace ray_tracing
{
    class material
    {
        /**
         * @brief 
         * 
         * @param r_in 
         * @param rec 
         * @param out_color 
         * @param out_scattered 
         * @return true continue ray tracing processing
         * @return false no scattered ray
         */
        virtual bool scatter(const ray &r_in, const hit_record &rec,
                             vec3 &out_color, ray &out_scattered) const = 0;
    };

    class lambertian : public material
    {
    public:
        vec3 albedo;
        float fuzziness;
        bool reflectable;

    public:
        lambertian(const vec3 &albedo_color, float fuzziness_ = 0, bool reflectable_ = true)
            : albedo(albedo_color), fuzziness(fuzziness_), reflectable(reflectable_) {}
        virtual bool scatter(const ray &r_in, const hit_record &rec,
                             vec3 &out_color, ray &out_scattered) const override
        {
            out_color = albedo;
            if (reflectable)
            {
                auto target = rec.position + rec.normal + random_vec3_in_unit_sphere();
                out_scattered = ray(rec.position, target - rec.position);
                return true;
            }
            else
                return false; // no scattered ray out
        }
    };

}