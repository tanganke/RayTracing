#include "sphere.h"

namespace ray_tracing
{
    vec2 get_unit_sphere_uv(const vec3 &p)
    {
        float phi = std::atan2(p.z, p.x);
        float theta = std::asin(p.y);
        float &&u = 1 - (phi + M_PI) / (2 * M_PI);
        float &&v = (theta + M_PI / 2) / M_PI;
        return vec2{u, v};
    }
}