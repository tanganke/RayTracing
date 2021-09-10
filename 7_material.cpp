#include <catch2/catch.hpp>
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"
#include "float.h"
#include <iostream>
#include <fstream>

static vec3 ray_color(const ray &r, Hitable *world, int depth)
{
    HitRecord rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec))
    {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * ray_color(scattered, world, depth + 1);
        }
        else
        {
            return vec3{0, 0, 0};
        }
    }
    else
    {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

TEST_CASE("material", "[material]")
{
    int nx{200};
    int ny{100};
    int ns{100};

    std::ofstream os("7_material.ppm");
    os << "P3\n"
       << nx << ' ' << ny << "\n255\n";

    Hitable *list[4];
    list[0] = new Sphere(vec3{0, 0, -1}, 0.5, std::make_shared<Lambertian>(vec3{0.8, 0.3, 0.3}));
    list[1] = new Sphere(vec3{0, -100.5, -1}, 100, std::make_shared<Lambertian>(vec3{0.8, 0.8, 0}));
    list[2] = new Sphere(vec3{1, 0, -1}, 0.5, std::make_shared<Metal>(vec3{0.8, 0.6, 0.2}));
    list[3] = new Sphere(vec3{-1, 0, -1}, 0.5, std::make_shared<Metal>(vec3{0.8, 0.8, 0.8}));
    Hitable *world = new HitableList{list, std::size(list)};

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
                col += ray_color(r, world, 0);
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

TEST_CASE("material_fuzz_metal", "[material]")
{
    int nx{200};
    int ny{100};
    int ns{100};

    std::ofstream os("7_material_fuzz_metal.ppm");
    os << "P3\n"
       << nx << ' ' << ny << "\n255\n";

    Hitable *list[4];
    list[0] = new Sphere(vec3{0, 0, -1}, 0.5, std::make_shared<Lambertian>(vec3{0.8, 0.3, 0.3}));
    list[1] = new Sphere(vec3{0, -100.5, -1}, 100, std::make_shared<Lambertian>(vec3{0.8, 0.8, 0}));
    list[2] = new Sphere(vec3{1, 0, -1}, 0.5, std::make_shared<Metal>(vec3{0.8, 0.6, 0.2}, 0.3));
    list[3] = new Sphere(vec3{-1, 0, -1}, 0.5, std::make_shared<Metal>(vec3{0.8, 0.8, 0.8}, 1));
    Hitable *world = new HitableList{list, std::size(list)};

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
                col += ray_color(r, world, 0);
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

TEST_CASE("material_large", "[material]")
{
    int nx{800};
    int ny{400};
    int ns{100};

    std::ofstream os("7_material_large.ppm");
    os << "P3\n"
       << nx << ' ' << ny << "\n255\n";

    Hitable *list[4];
    list[0] = new Sphere(vec3{0, 0, -1}, 0.5, std::make_shared<Lambertian>(vec3{0.8, 0.3, 0.3}));
    list[1] = new Sphere(vec3{0, -100.5, -1}, 100, std::make_shared<Lambertian>(vec3{0.8, 0.8, 0}));
    list[2] = new Sphere(vec3{1, 0, -1}, 0.5, std::make_shared<Metal>(vec3{0.8, 0.6, 0.2}));
    list[3] = new Sphere(vec3{-1, 0, -1}, 0.5, std::make_shared<Metal>(vec3{0.8, 0.8, 0.8}));
    Hitable *world = new HitableList{list, std::size(list)};

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
                col += ray_color(r, world, 0);
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