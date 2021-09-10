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
        material *mat_ptr;
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
            std::vector<bool> is_hit(list.size());
            std::vector<hit_record> hit_records(list.size());
            std::vector<int> indices(list.size());

            std::iota(indices.begin(), indices.end(), 0);
            std::transform(std::execution::par_unseq,
                           indices.begin(), indices.end(),
                           is_hit.begin(),
                           [&](int i) -> bool
                           { return list[i]->hit(ray, t_min, t_max, hit_records[i]); });

            hit_record *temp_rec;
            bool hit_anything = false;
            float close_so_far = t_max;
            for (int i = 0; i < indices.size(); ++i)
            {
                if (is_hit[i] && hit_records[i].ray_parameter < close_so_far)
                {
                    hit_anything = true;
                    temp_rec = &hit_records[i];
                    close_so_far = hit_records[i].ray_parameter;
                }
            }
            if (hit_anything)
                out_record = *temp_rec;
            return hit_anything;
        }
    };

}