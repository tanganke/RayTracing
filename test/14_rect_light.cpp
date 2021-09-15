#include <catch2/catch.hpp>
#include "RayTracing/perlin.h"
#include "RayTracing/camera.h"
#include "RayTracing/ray.h"
#include "RayTracing/hittable.h"
#include "RayTracing/sphere.h"
#include "RayTracing/material.h"
#include "RayTracing/color.h"
#include "RayTracing/progress_bar.h"
#include "RayTracing/render.h"
#include "RayTracing/rectangle.h"
#include "RayTracing/light.h"
#include <iostream>
#include <fstream>
#include <stb/stb_image_write.h>

using namespace ray_tracing;

TEST_CASE("rect_light", "[rect_light]")
{
    int nx{300};
    int ny{300};
    int ns{150};

    vec3 look_from{13, 2, 5};
    vec3 look_at{0, 0, 0};
    camera cam{look_from, look_at, {0, 1, 0}, degree_to_radian(40), float(nx) / ny};

    hittable_vector world;
    std::shared_ptr<perlin_noise_texture> perlin_texture = std::make_shared<perlin_noise_texture>();
    {
        perlin_texture->smooth = 2;
        perlin_texture->scale = 2;
    }
    std::shared_ptr<lambertian> perlin_material = std::make_shared<lambertian>(perlin_texture);
    std::shared_ptr<lambertian> image_material = std::make_shared<lambertian>(std::make_shared<image_texture>("data/earth.jpg"));
    std::shared_ptr<diffuse_light> white_light = std::make_shared<diffuse_light>(std::make_shared<constant_texture>(vec3{0.4, 0.4, 0.4}));
    world.push_back(std::make_shared<sphere>(vec3{0, -1000, 0}, 1000, perlin_material))
        .push_back(std::make_shared<sphere>(vec3{0, 2, 0}, 2, image_material))
        .push_back(std::make_shared<sphere>(vec3{0, 7, 0}, 2, white_light))
        .push_back(std::make_shared<xy_rect>(-5, 5, 1, 3, -3, white_light))
        .push_back(std::make_shared<xy_rect>(-5, 5, 1, 3, -2.5, image_material));
    progress_bar bar;

    auto image_data = render(nx, ny, ns, cam, world);
    stbi_write_png("rect_light.png", nx, ny, 3, (void *)&image_data[0], 0);
}

TEST_CASE("xy_rect", "[rect_light]")
{
    int nx{300};
    int ny{300};
    int ns{150};

    vec3 look_from{1, 1, 1};
    vec3 look_at{0, 0, 0};
    camera cam{look_from, look_at, {0, 1, 0}, degree_to_radian(40), float(nx) / ny};

    hittable_vector world;
    std::shared_ptr<diffuse_light> white_light = std::make_shared<diffuse_light>(std::make_shared<constant_texture>(vec3{0.4, 0.4, 0.4}));
    world.push_back(std::make_shared<xy_rect>(-5, 5, -5, 5, 0, white_light));
    progress_bar bar;

    auto image_data = render(nx, ny, ns, cam, world);
    stbi_write_png("xy_rect.png", nx, ny, 3, (void *)&image_data[0], 0);
}

TEST_CASE("zx_rect", "[rect_light]")
{
    int nx{300};
    int ny{300};
    int ns{150};

    vec3 look_from{1, 1, 1};
    vec3 look_at{0, 0, 0};
    camera cam{look_from, look_at, {0, 1, 0}, degree_to_radian(40), float(nx) / ny};

    hittable_vector world;
    std::shared_ptr<diffuse_light> white_light = std::make_shared<diffuse_light>(std::make_shared<constant_texture>(vec3{0.4, 0.4, 0.4}));
    world.push_back(std::make_shared<zx_rect>(-5, 5, -5, 5, 0, white_light));
    progress_bar bar;

    auto image_data = render(nx, ny, ns, cam, world);
    stbi_write_png("zx_rect.png", nx, ny, 3, (void *)&image_data[0], 0);
}

TEST_CASE("yz_rect", "[rect_light]")
{
    int nx{300};
    int ny{300};
    int ns{150};

    vec3 look_from{1, 1, 1};
    vec3 look_at{0, 0, 0};
    camera cam{look_from, look_at, {0, 1, 0}, degree_to_radian(40), float(nx) / ny};

    hittable_vector world;
    std::shared_ptr<diffuse_light> white_light = std::make_shared<diffuse_light>(std::make_shared<constant_texture>(vec3{0.4, 0.4, 0.4}));
    world.push_back(std::make_shared<yz_rect>(-5, 5, -5, 5, 0, white_light));
    progress_bar bar;

    auto image_data = render(nx, ny, ns, cam, world);
    stbi_write_png("yz_rect.png", nx, ny, 3, (void *)&image_data[0], 0);
}
