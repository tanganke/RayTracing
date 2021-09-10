#include <catch2/catch.hpp>
#include "RayTracing/sphere.h"
#include "float.h"
#include <iostream>
#include <fstream>

using namespace ray_tracing;

static vec3 color(const ray &r, hittable *world)
{
    hit_record rec;
    if (world->hit(r, 0, MAXFLOAT, rec))
    {
        return 0.5 * (rec.normal + float(1));
    }
    else
    {
        vec3 unit_direction = unit_vector(r.direction);
        float t = 0.5 * (unit_direction.y + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

TEST_CASE("hitables", "[hitables]")
{
    int nx{200};
    int ny{100};

    std::ofstream os("4_hitables.ppm");
    os << "P3\n"
       << nx << ' ' << ny << "\n255\n";
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4, 0, 0);
    vec3 vertical(0, 2, 0);
    vec3 origin(0, 0, 0);

    hittable_vector world;
    world.push_back(std::make_shared<sphere>(vec3{0, 0, -1}, 0.5))
        .push_back(std::make_shared<sphere>(vec3{0, -100.5, -1}, 100));

    for (int j = ny - 1; j >= 0; j--)
        for (int i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = color(r, &world);
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            os << ir << ' ' << ig << ' ' << ib << '\n';
        }
}
