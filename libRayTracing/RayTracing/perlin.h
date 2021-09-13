#pragma once
#include "vec.h"
#include "texture.h"

namespace ray_tracing
{
    float perlin_noise(const vec3 &p);
    float perlin_noise_trilinear_interp(const vec3 &p);
    float perlin_noise_hermite_cubic(const vec3 &p);

    class perlin_noise_texture : public texture
    {
    public:
        perlin_noise_texture() = default;
        virtual vec3 value(float u, float v, const vec3 &p) const override
        {
            float (*noise_func)(const vec3 &p);
            switch (smooth)
            {
            case 1:
                noise_func = &perlin_noise_trilinear_interp;
                break;
            case 2:
                noise_func = &perlin_noise_hermite_cubic;
                break;
            case 0:
            default:
                noise_func = &perlin_noise;
                break;
            }

            return vec3(1, 1, 1) * noise_func(scale * p);
        }

        /**
         * @brief 0 no smooth
         *        1 trilinear interpolation
         *        2 hermite cubic interpolation
         */
        int smooth{};
        float scale{1};
    };
}