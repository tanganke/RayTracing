#include <catch2/catch.hpp>
#include "RayTracing/ray.h"
#include <iostream>
#include <fstream>

using namespace ray_tracing;

static bool hit_sphere(const vec3 &center, float radius, const ray &r)
{
    vec3 oc = r.origin() - center;
    float a = dot(r.direction, r.direction);
    float b = 2 * dot(oc, r.direction);
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    return discriminant > 0;
}

static vec3 color(const ray &r)
{
    if (hit_sphere(vec3(0, 0, -1), 0.5, r))
        return vec3(1, 0, 0);
    vec3 unit_direction = unit_vector(r.direction);
    float t = 0.5 * (unit_direction.y + 1.0);
    return (1.0f - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

TEST_CASE("hit_sphere", "[hit_sphere]")
{
    int nx{200};
    int ny{100};

    std::ofstream os("2_hit_sphere.ppm");
    os << "P3\n"
       << nx << ' ' << ny << "\n255\n";
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4, 0, 0);
    vec3 vertical(0, 2, 0);
    vec3 origin(0, 0, 0);

    for (int j = ny - 1; j >= 0; j--)
        for (int i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = color(r);
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            os << ir << ' ' << ig << ' ' << ib << '\n';
        }
}
