#pragma once
#include "material.h"
#include "texture.h"

namespace ray_tracing
{
    class diffuse_light : public material
    {
    public:
        diffuse_light(std::shared_ptr<texture> emit_tex) : emit{emit_tex} {}
        virtual bool scatter(const ray &r_in, const hit_record &rec,
                             vec3 &out_color, ray &out_scattered) const override { return false; }

        virtual vec3 emmitted(const hit_record &rec) const override
        {
            float u = rec.uv_coord[0];
            float v = rec.uv_coord[1];
            auto p = rec.position;
            return emit->value(u, v, p);
        }

        std::shared_ptr<texture> emit;
    };
}