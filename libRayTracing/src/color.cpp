#include "color.h"

namespace ray_tracing
{
    const vec3 DEBUG_COLOR{0.8, 0, 0.2};

    vec3 ray_color(const ray &r, hittable *world, int depth)
    {
        hit_record rec;
        if (world->hit(r, 0.001, MAXFLOAT, rec))
        {
            ray scattered;
            vec3 attenuation;
            if (depth < 50)
            {
                if (rec.mat_ptr && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
                    return attenuation * ray_color(scattered, world, depth + 1);
                else
                    return DEBUG_COLOR;
            }
            else
            {
                return vec3{0, 0, 0};
            }
        }
        else
        {
            vec3 unit_direction = unit_vector(r.direction);
            float t = 0.5 * (unit_direction.y + 1.0);
            return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
        }
    }

}