#include "random.h"

namespace ray_tracing
{
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