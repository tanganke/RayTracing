#pragma once
#include "ray.h"

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
        inline ray get_ray(float u, float v)
        {
            return ray(origin, lower_left_corner + u * horizontal + v * vertical);
        }

    private:
        vec3 origin;
        vec3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
    };

}