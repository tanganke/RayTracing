#include <catch2/catch.hpp>
#include "RayTracing/perlin.h"
#include "RayTracing/camera.h"
#include "RayTracing/ray.h"
#include "RayTracing/hittable.h"
#include "RayTracing/sphere.h"
#include "RayTracing/material.h"
#include "RayTracing/color.h"
#include "RayTracing/progress_bar.h"
#include <iostream>
#include <fstream>

using namespace ray_tracing;

TEST_CASE("image_texture", "[perlin]")
{
    int nx{800};
    int ny{400};
    int ns{50};

    std::ofstream os("image_texture.ppm");
    os << "P3\n"
       << nx << ' ' << ny << "\n255\n";

    vec3 look_from{13, 2, 3};
    vec3 look_at{0, 0, 0};
    camera cam{look_from, look_at, {0, 1, 0}, 20, float(nx) / ny};

    hittable_vector world;
    std::shared_ptr<perlin_noise_texture> perlin_texture = std::make_shared<perlin_noise_texture>();
    perlin_texture->smooth = 3;
    perlin_texture->scale = 2;
    std::shared_ptr<lambertian> perlin_material = std::make_shared<lambertian>(perlin_texture);
    std::shared_ptr<lambertian> image_material = std::make_shared<lambertian>(std::make_shared<image_texture>("data/earth.jpg"));
    world.push_back(std::make_shared<sphere>(vec3{0, -1000, 0}, 1000, perlin_material))
        .push_back(std::make_shared<sphere>(vec3{0, 2, 0}, 2, image_material));

    progress_bar bar;

    for (int j = ny - 1; j >= 0; j--)
        for (int i = 0; i < nx; i++)
        {
            vec3 col(0, 0, 0);
            std::vector<ray> raies;
            for (int s = 0; s < ns; ++s)
            {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                raies.push_back(cam.get_ray(u, v));
            }

            col = ray_color(raies, world, 0);
            col = vec3{sqrt(col.x), sqrt(col.y), sqrt(col.z)};
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            os << ir << ' ' << ig << ' ' << ib << '\n';
            if (j % 9 == 0 && i == 0)
                bar.set_progress(static_cast<size_t>(((ny - j) * nx + (i + 1)) * 100 / (nx * ny)));
        }
}