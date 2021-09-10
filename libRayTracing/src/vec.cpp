#include "vec.h"

namespace ray_tracing
{
    const float DEGREE = M_PI / 180;

    vec3 refract(const vec3 &v, const vec3 &n, float ni_over_nt)
    {
        auto unit_v = unit_vector(v);
        auto unit_n = unit_vector(n);

        float cos_i = dot(unit_v, n);
        float sin_i = std::sqrt(1 - cos_i * cos_i);
        auto vi_para = unit_v - (unit_n * cos_i);
        auto vi_prep = unit_v - vi_para;
        auto vt_para = vi_para * ni_over_nt;
        auto vt_para_length = length(vt_para);
        if (vt_para_length > 1)
            return unit_vector(vt_para);
        else
        {
            auto vt_prep = unit_vector(vi_prep) * std::sqrt((1 - squared_length(vt_para)));
            return vt_para + vt_prep;
        }
    }

    vec3 refract(const vec3 &v, const vec3 &n, float ni_over_nt, bool &is_total_reflection)
    {
        auto unit_v = unit_vector(v);
        auto unit_n = unit_vector(n);

        float cos_i = dot(unit_v, n);
        float sin_i = std::sqrt(1 - cos_i * cos_i);
        auto vi_para = unit_v - (unit_n * cos_i);
        auto vi_prep = unit_v - vi_para;
        auto vt_para = vi_para * ni_over_nt;
        auto vt_para_length = length(vt_para);
        if (vt_para_length > 1)
        {
            return unit_vector(vt_para);
            is_total_reflection = true;
        }
        else
        {
            auto vt_prep = unit_vector(vi_prep) * std::sqrt((1 - squared_length(vt_para)));
            is_total_reflection = false;
            return vt_para + vt_prep;
        }
    }
}