#pragma once
#include "vec.h"
#include "random.h"
#include "texture.h"

namespace ray_tracing
{
    float perlin_noise(const vec3 &p);
    float perlin_noise_trilinear_interp(const vec3 &p);
    float perlin_noise_hermite_cubic(const vec3 &p);
    float perlin_noise_hermite_cubic_vec(const vec3 &p);

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
            case 3:
                noise_func = perlin_noise_hermite_cubic_vec;
                break;
            case 0:
            default:
                noise_func = &perlin_noise;
                break;
            }
            if (smooth == 3)
                return vec3(1, 1, 1) * 0.5 * (1 + noise_func(scale * p));
            else
                return vec3(1, 1, 1) * noise_func(scale * p);
        }

        /**
         * @brief 0 no smooth
         *        1 trilinear interpolation
         *        2 hermite cubic interpolation
         *        3 hermite cubic interpolation vec3
         */
        int smooth{3};
        float scale{1};
    };
}