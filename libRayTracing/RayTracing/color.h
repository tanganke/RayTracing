#pragma once
#include "material.h"
#include "hitable.h"

namespace ray_tracing
{
    extern const vec3 DEBUG_COLOR;
    vec3 ray_color(const ray &r, const hittable &world, int depth);
    vec3 ray_color(const std::vector<ray> &r, const hittable &world, int depth);
}
