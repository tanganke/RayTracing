#pragma once
#include "ray.h"
#include "random.h"

namespace ray_tracing
{

    class camera
    {
    public:
        camera() : lower_left_corner(-2.0, -1.0, -1.0),
                   horizontal(4, 0, 0),
                   vertical(0, 2, 0),
                   origin(0, 0, 0)
        {
        }

        /**
         * @brief Construct a new camera object
         * 
         * @param vfov in radians
         * @param aspect 
         */
        camera(float vfov, float aspect)
        {
            float half_height = std::tan(vfov / 2);
            float half_width = aspect * half_height;
            lower_left_corner = vec3{-half_width, -half_height, -1.0};
            horizontal = vec3{2 * half_width, 0, 0};
            vertical = vec3(0, 2 * half_height, 0);
            origin = vec3(0, 0, 0);
        }

        camera(const vec3 &look_from, const vec3 &look_at, const vec3 &up, float vfov, float aspect)
        {
            float half_height = std::tan(vfov / 2);
            float half_width = aspect * half_height;
            origin = look_from;
            w = unit_vector(look_from - look_at);
            u = unit_vector(cross(up, w));
            v = cross(w, u);
            lower_left_corner = origin - half_width * u - half_height * v - w;
            horizontal = 2 * half_width * u;
            vertical = 2 * half_height * v;
        }

        inline ray get_ray(float s, float t)
        {
            vec2 rd = lens_radius * random_vec2_in_unit_disk();
            auto offset = u * rd.x + v * rd.y;
            auto target = lower_left_corner + s * horizontal + t * vertical;
            auto start = origin + offset;
            return ray(start, target - start);
        }

    private:
        vec3 origin;
        vec3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        vec3 u, v, w;

    public:
        float lens_radius{};
    };

}