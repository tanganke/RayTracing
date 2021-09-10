#pragma once
#include "ray.h"
#include "hitable.h"
#include "random.h"

namespace ray_tracing
{
    
    class material
    {
    public:
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

    public:
        lambertian(const vec3 &albedo_color, float fuzziness_ = 0, bool reflectable_ = true)
            : albedo(albedo_color), fuzziness(fuzziness_) {}
        virtual bool scatter(const ray &r_in, const hit_record &rec,
                             vec3 &out_color, ray &out_scattered) const override
        {
            out_color = albedo;

            auto target = rec.position + rec.normal + random_vec3_in_unit_sphere();
            out_scattered = ray(rec.position, target - rec.position);
            return true;
        }
    };

    class metal : public material
    {
    public:
        vec3 albedo;
        float fuzziness;

    public:
        metal(const vec3 &albedo_, float fuzz_ = 0) : albedo(albedo_), fuzziness(fuzz_)
        {
            fuzziness = fuzz_;
            fuzziness = clamp(fuzziness, 0, 1);
        }

        virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &out_color, ray &out_scattered) const
        {
            vec3 reflected = reflect(unit_vector(r_in.direction), rec.normal);
            if (fuzziness > 0)
            {
                out_scattered = ray(rec.position, reflected + fuzziness * random_vec3_in_unit_sphere());
            }
            else
            {
                out_scattered = ray(rec.position, reflected);
            }
            out_color = albedo;
            return dot(out_scattered.direction, rec.normal) > 0;
        }
    };

    class dielectric : public material
    {
    public:
        float index_of_refraction;

    public:
        dielectric(float index_of_refraction_) : index_of_refraction{index_of_refraction_} {}

        virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &out_color, ray &out_scattered) const
        {
            out_color = vec3{1, 1, 1};
            float ni_over_nt = rec.front_face ? (1 / index_of_refraction) : index_of_refraction;
            bool is_total_reflection;
            auto refracted = refract(r_in.direction, rec.normal, ni_over_nt, is_total_reflection);
            if (is_total_reflection)
                out_scattered = ray{rec.position, reflect(r_in.direction, rec.normal)};
            else
                out_scattered = ray{rec.position, refracted};
            return true;
        }
    };

}