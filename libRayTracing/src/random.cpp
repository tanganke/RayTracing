#include "random.h"

namespace ray_tracing
{
    vec2 random_vec2_in_unit_disk()
    {
        vec2 ans;
    TRY:
        ans = vec2{random<float>(-1, 1), random<float>(-1, 1)};
        if (length(ans) >= 1)
            goto TRY;
        return ans;
    }
    vec3 random_vec3_in_unit_sphere()
    {
        vec3 ans;
    TRY:
        ans = random_vec3(-1, 1);
        if (length(ans) >= 1)
            goto TRY;
        return ans;
    }
}