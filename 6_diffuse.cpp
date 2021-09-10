#include <catch2/catch.hpp>
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "float.h"
#include <iostream>
#include <fstream>

static vec3 ray_color(const ray &r, Hitable *world)
{
    HitRecord rec;
    if (world->hit(r, 0, MAXFLOAT, rec))
    {
        auto target = rec.p + rec.normal + random_vec3_in_unit_sphere<float>();
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world);
    }
    else
    {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

TEST_CASE("diffuse", "[diffuse]")
{
    int nx{200};
    int ny{100};
    int ns{100};

    std::ofstream os("6_diffuse.ppm");
    os << "P3\n"
       << nx << ' ' << ny << "\n255\n";

    Hitable *list[2];
    list[0] = new Sphere(vec3{0, 0, -1}, 0.5);
    list[1] = new Sphere(vec3{0, -100.5, -1}, 100);
    Hitable *world = new HitableList{list, 2};

    Camera cam;
    for (int j = ny - 1; j >= 0; j--)
        for (int i = 0; i < nx; i++)
        {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; ++s)
            {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                ray r = cam.get_ray(u, v);
                col += ray_color(r, world);
            }
            col /= float(ns);
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            os << ir << ' ' << ig << ' ' << ib << '\n';
        }

    delete list[0];
    delete list[1];
    delete world;
}

TEST_CASE("diffuse_gamma", "[diffuse]")
{
    int nx{200};
    int ny{100};
    int ns{100};

    std::ofstream os("6_diffuse_gamma.ppm");
    os << "P3\n"
       << nx << ' ' << ny << "\n255\n";

    Hitable *list[2];
    list[0] = new Sphere(vec3{0, 0, -1}, 0.5);
    list[1] = new Sphere(vec3{0, -100.5, -1}, 100);
    Hitable *world = new HitableList{list, 2};

    Camera cam;
    for (int j = ny - 1; j >= 0; j--)
        for (int i = 0; i < nx; i++)
        {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; ++s)
            {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                ray r = cam.get_ray(u, v);
                col += ray_color(r, world);
            }
            col /= float(ns);
            col = vec3{sqrt(col.x()), sqrt(col.y()), sqrt(col.z())};
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            os << ir << ' ' << ig << ' ' << ib << '\n';
        }

    delete list[0];
    delete list[1];
    delete world;
}