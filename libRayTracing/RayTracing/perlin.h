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
            return vec3(1, 1, 1) * noise(p);
        }

        float noise(const vec3 &p) const
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

            return noise_func(scale * p);
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

    class turbulence_noise_texture : public perlin_noise_texture
    {
        float turb(const vec3 &p, int depth) const
        {
            float accum = 0;
            vec3 temp_p = p;
            float weight = 1;
            for (int i = 0; i < depth; i++)
            {
                accum += weight * noise(temp_p);
                weight *= 0.5;
                temp_p *= 2;
            }
            return std::abs(accum);
        }

    public:
        virtual vec3 value(float u, float v, const vec3 &p) const override
        {
            return vec3(1, 1, 1) * turb(p, depth); //! not correct
        }

        int depth{7};
    };
}