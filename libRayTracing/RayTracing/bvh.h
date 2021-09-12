#pragma once
#include "hittable.h"

namespace ray_tracing
{
    struct bvh_node : public hittable
    {
        aabb bbox;
        std::shared_ptr<bvh_node> left, right;
        bvh_node *parent{nullptr};

        bvh_node() = default;

        virtual bool hit(const ray &r, float t_min, float t_max, hit_record &out_record) const override
        {
            if (bbox.hit(r, t_min, t_max))
            {
                hit_record left_rec, right_rec;
                bool left_hit{false}, right_hit{false};
                if (left)
                    left_hit = left->hit(r, t_min, t_max, left_rec);
                if (right)
                    right_hit = right->hit(r, t_min, t_max, right_rec);

                if (left_hit && right_hit)
                {
                    if (left_rec.ray_parameter < right_rec.ray_parameter)
                        out_record = left_rec;
                    else
                        out_record = right_rec;
                    return true;
                }

                if (left_hit)
                {
                    out_record = out_record;
                    return true;
                }

                if (right_hit)
                {
                    out_record = right_rec;
                    return true;
                }

                return false;
            }
            else
                return false;
        }

        virtual bool bounding_box(aabb &out_aabb) const override
        {
            out_aabb = bbox;
            return true;
        }
    };
}