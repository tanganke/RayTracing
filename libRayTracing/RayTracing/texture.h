#pragma once
#include "vec.h"
#include "hittable.h"
#include <memory>

namespace ray_tracing
{
    class texture
    {
    public:
        virtual vec3 value(float u, float v, const vec3 &p) const { return vec3{0.8, 0, 0.2}; };
    };

    class constant_texture : public texture
    {
    public:
        vec3 color;

        constant_texture() : color{0.8, 0, 0.2} {}
        constant_texture(const vec3 &c) : color{c} {}
        virtual vec3 value(float u, float v, const vec3 &p) const override { return color; }
    };

    class checker_texture : public texture
    {
    public:
        std::shared_ptr<texture> odd;
        std::shared_ptr<texture> even;

        checker_texture(std::shared_ptr<texture> odd_, std::shared_ptr<texture> even_) : odd{odd_}, even{even_} {}
        virtual vec3 value(float u, float v, const vec3 &p) const override
        {
            float sines = std::sin(10 * p.x) * std::sin(10 * p.y) + std::sin(10 * p.z);
            if (sines < 0)
                return odd->value(u, v, p);
            else
                return even->value(u, v, p);
        }
    };
}