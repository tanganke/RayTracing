#pragma once
#include "ray.h"
#include "material.h"

namespace ray_tracing
{
    struct hit_record
    {
        float ray_parameter;
        vec3 position;
        vec3 normal;
        material *material;
    };

    class Hitable
    {
    public:
        /**
     * @brief 
     * 
     * @param ray 
     * @param t_min 
     * @param t_max 
     * @param out_record 
     * @return true input ray hit the object
     * @return false 
     */
        virtual bool hit(const ray &ray, float t_min, float t_max, hit_record &out_record) const = 0;
    };

}