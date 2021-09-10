#include <catch2/catch.hpp>
#include "RayTracing/sphere.h"
#include "RayTracing/camera.h"
#include "RayTracing/material.h"
#include "RayTracing/random.h"
#include "float.h"
#include <iostream>
#include <fstream>

using namespace ray_tracing;

static vec3 ray_color(const ray &r, hittable *world, int depth)
{
    hit_record rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec))
    {
        ray scattered;
        vec3 attenuation;
        if (depth < 50)
        {
            if (rec.mat_ptr && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
                return attenuation * ray_color(scattered, world, depth + 1);
            else
                return vec3(0.8, 0, 0.2);
        }
        else
        {
            return vec3{0.8, 0, 0.2};
        }
    }
    else
    {
        vec3 unit_direction = unit_vector(r.direction);
        float t = 0.5 * (unit_direction.y + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

TEST_CASE("random_scene", "[random_scene]")
{
    int nx{800};
    int ny{400};
    int ns{50};

    std::ofstream os("9_random_scene.ppm");
    os << "P3\n"
       << nx << ' ' << ny << "\n255\n";

    hittable_vector world;
    for (float x = -11; x <= 11; x++)
        for (float y = -11; y <= 11; y++)
        {
            float r = random<float>();
            if (random<int>())
                world.push_back(std::make_shared<sphere>(vec3{x, y, r + random<float>()}, r, std::make_shared<lambertian>(random<vec3>())));
            else
                world.push_back(std::make_shared<sphere>(vec3{x, y, r + random<float>()}, r, std::make_shared<metal>(random<vec3>())));
        }

    world.push_back(std::make_shared<sphere>(vec3{0, 0, -1}, 0.5, std::make_shared<lambertian>(vec3{0.8, 0.3, 0.3})))
        .push_back(std::make_shared<sphere>(vec3{0, -100.5, -1}, 100, std::make_shared<lambertian>(vec3{0.8, 0.8, 0})))
        .push_back(std::make_shared<sphere>(vec3{1, 0, -1}, 0.5, std::make_shared<metal>(vec3{0.8, 0.6, 0.2})))
        .push_back(std::make_shared<sphere>(vec3{-1, 0, -1}, 0.5, std::make_shared<dielectric>(1.5)))
        .push_back(std::make_shared<sphere>(vec3{-1, 0, -1}, -0.45, std::make_shared<dielectric>(1.5)));

    camera cam(vec3{-11, 2, -11}, vec3{0, 0, 0}, vec3{0, 1, 0}, degree_to_radian(90), float(nx) / ny);
    for (int j = ny - 1; j >= 0; j--)
        for (int i = 0; i < nx; i++)
        {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; ++s)
            {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                ray r = cam.get_ray(u, v);
                col += ray_color(r, &world, 0);
            }
            col /= float(ns);
            col = vec3{sqrt(col.x), sqrt(col.y), sqrt(col.z)};
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            os << ir << ' ' << ig << ' ' << ib << '\n';
        }
}