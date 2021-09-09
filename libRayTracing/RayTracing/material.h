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
        lambertian(const vec3 &a) : albedo(a) {}
        virtual bool scatter(const ray &r_in, const hit_record &rec,
                             vec3 &out_color, ray &out_scattered) const override
        {
            auto target = rec.position + rec.normal + random_vec3_in_unit_sphere();
            out_scattered = ray(rec.position, target - rec.position);
            out_color = albedo;
            return true;
        }

    private:
        vec3 albedo;
    };

}