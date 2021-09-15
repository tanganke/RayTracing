#pragma once
#include "vec.h"
#include "hittable.h"
#include "stb/stb_image.h"
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
        vec3 color;
    public:

        constant_texture() : color{0.8, 0, 0.2} {}
        constant_texture(const vec3 &c) { color = c; }
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

    class image_texture : public texture
    {
    public:
        image_texture() = default;
        image_texture(const std::string &path)
        {
            data_ptr.reset(stbi_load(path.c_str(), &width, &height, nullptr, 3));
        }
        virtual vec3 value(float u, float v, const vec3 &p) const override
        {
            int i = u * width;
            int j = (1 - v) * height - 0.001;
            i = clamp<int>(i, 0, width - 1);
            j = clamp<int>(j, 0, height - 1);
            float &&r = int((data_ptr.get())[3 * i + 3 * width * j]) / 255.0;
            float &&g = int((data_ptr.get())[3 * i + 3 * width * j + 1]) / 255.0;
            float &&b = int((data_ptr.get())[3 * i + 3 * width * j + 2]) / 255.0;
            return vec3{r, g, b};
        }

        std::shared_ptr<uint8_t> data_ptr;
        int width, height;
    };
}