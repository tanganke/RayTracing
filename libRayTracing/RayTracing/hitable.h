#pragma once
#include "ray.h"
#include <memory>
#include <vector>
#include <algorithm>
#include <execution>

namespace ray_tracing
{
    class material;
    struct hit_record
    {
        float ray_parameter;
        vec3 position;
        vec3 normal;
        bool front_face;
        material *mat_ptr{nullptr};
    };

    class hittable
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

    class hittable_vector : public hittable
    {
    private:
        std::vector<std::shared_ptr<hittable>> list;

    public:
        inline hittable_vector &push_back(std::shared_ptr<hittable> hittable_ptr)
        {
            list.push_back(hittable_ptr);
            return *this;
        }

        virtual bool hit(const ray &ray, float t_min, float t_max, hit_record &out_record) const
        {
            bool hit_anything = false;
            float close_so_far = t_max;
            hit_record temp_record;

            for (auto it = list.begin(); it != list.end(); it++)
            {
                auto &hittable_ptr = *it;
                if (hittable_ptr->hit(ray, t_min, close_so_far, temp_record))
                    if (temp_record.ray_parameter < close_so_far)
                    {
                        hit_anything = true;
                        out_record = temp_record;
                        close_so_far = temp_record.ray_parameter;
                    }
            }

            return hit_anything;
        }
    };

}