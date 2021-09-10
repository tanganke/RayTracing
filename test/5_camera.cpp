#include <catch2/catch.hpp>
#include "RayTracing/sphere.h"
#include "RayTracing/camera.h"
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
        vec3 unit_direction = r.unit_direction();
        float t = 0.5 * (unit_direction.y + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

TEST_CASE("camera", "[camera]")
{
    int nx{200};
    int ny{100};
    int ns{100};

    std::ofstream os("5_camera.ppm");
    os << "P3\n"
       << nx << ' ' << ny << "\n255\n";

    hittable_vector world;
    world.push_back(std::make_shared<sphere>(vec3{0, 0, -1}, 0.5))
        .push_back(std::make_shared<sphere>(vec3{0, -100.5, -1}, 100));

    camera cam;
    for (int j = ny - 1; j >= 0; j--)
        for (int i = 0; i < nx; i++)
        {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; ++s)
            {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, &world);
            }
            col /= float(ns);
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            os << ir << ' ' << ig << ' ' << ib << '\n';
        }
}
