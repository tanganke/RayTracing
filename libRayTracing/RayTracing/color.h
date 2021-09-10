#pragma once
#include "material.h"
#include "hitable.h"

namespace ray_tracing
{
    extern const vec3 DEBUG_COLOR;
    vec3 ray_color(const ray &r, hittable *world, int depth);

}
