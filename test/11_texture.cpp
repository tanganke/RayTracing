#include <catch2/catch.hpp>
#include "RayTracing/sphere.h"
#include "RayTracing/camera.h"
#include "RayTracing/material.h"
#include "RayTracing/random.h"
#include "RayTracing/color.h"
#include <indicators/indicators.hpp>
#include <thread>
#include <chrono>
#include "float.h"
#include <iostream>
#include <fstream>

using namespace ray_tracing;

TEST_CASE("random_scene_texture", "[texture]")
{
    int nx{800};
    int ny{400};
    int ns{50};

    std::ofstream os("11_random_scene_texture.ppm");
    os << "P3\n"
       << nx << ' ' << ny << "\n255\n";

    hittable_vector world;
    for (float x = -3; x <= 3; x += random<float>(0, 0.3))
        for (float y = -3; y <= 3; y += random<float>(0.3, 0.5))
        {
            float r = 0.15 * random<float>();
            if (random<int>())
                world.push_back(std::make_shared<sphere>(vec3{x, -0.5f + r + r * 0.5f * random<float>(), y}, r, std::make_shared<lambertian>(random<vec3>())));
            else
                world.push_back(std::make_shared<sphere>(vec3{x, -0.5f + r + r * 0.5f * random<float>(), y}, r, std::make_shared<metal>(random<vec3>())));
        }

    world.push_back(std::make_shared<sphere>(vec3{0, 0, -1}, 0.5, std::make_shared<lambertian>(vec3{0.8, 0.3, 0.3})))
        .push_back(std::make_shared<sphere>(vec3{0, -100.5, -1}, 100,
                                            std::make_shared<lambertian>(
                                                std::make_shared<checker_texture>(
                                                    std::make_shared<constant_texture>(vec3{0.2, 0.3, 0.1}),
                                                    std::make_shared<constant_texture>(vec3{0.9, 0.9, 0.9})))))
        .push_back(std::make_shared<sphere>(vec3{1, 0, -1}, 0.5, std::make_shared<metal>(vec3{0.8, 0.6, 0.2})))
        .push_back(std::make_shared<sphere>(vec3{-1, 0, -1}, 0.5, std::make_shared<dielectric>(1.5)))
        .push_back(std::make_shared<sphere>(vec3{-1, 0, -1}, -0.45, std::make_shared<dielectric>(1.5)));

    camera cam(vec3{-0.3, 0, 0.2}, vec3{0, 0, -1}, vec3{0, 1, 0}, degree_to_radian(90), float(nx) / ny);

    indicators::ProgressBar bar{
        indicators::option::BarWidth{50},
        indicators::option::Start{"["},
        indicators::option::Fill{"="},
        indicators::option::Lead{">"},
        indicators::option::Remainder{" "},
        indicators::option::End{"]"},
        indicators::option::PostfixText{"Rendering"},
        indicators::option::ForegroundColor{indicators::Color::green},
        indicators::option::FontStyles{std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}};

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
            bar.set_progress(static_cast<size_t>(((ny - j) * nx + (i + 1)) * 100 / (nx * ny)));
        }
}