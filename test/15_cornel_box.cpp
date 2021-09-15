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
#include "RayTracing/cuboid.h"
#include "RayTracing/translate.h"
#include "RayTracing/rotate.h"
#include <iostream>
#include <fstream>
#include <stb/stb_image_write.h>

using namespace ray_tracing;

TEST_CASE("cornell_box", "[cornell_box]")
{
    int nx{200};
    int ny{200};
    int ns{100};

    vec3 look_from{278, 278, -800};
    vec3 look_at{278, 278, 0};
    camera cam{look_from, look_at, {0, 1, 0}, degree_to_radian(40), float(nx) / ny};
    cam.lens_radius = 0;

    auto tex1 = std::make_shared<constant_texture>(vec3{15, 15, 15});
    auto tex_red = std::make_shared<constant_texture>(vec3{0.65, 0.05, 0.05});
    auto tex_white = std::make_shared<constant_texture>(vec3{0.73, 0.73, 0.73});
    auto tex_green = std::make_shared<constant_texture>(vec3{0.12, 0.45, 0.15});
    auto light = std::make_shared<diffuse_light>(tex1);
    auto red = std::make_shared<lambertian>(tex_red);
    auto white = std::make_shared<lambertian>(tex_white);
    auto green = std::make_shared<lambertian>(tex_green);

    hittable_vector world;
    world.push_back(std::make_shared<zx_rect>(213, 343, 227, 332, 554, light));
    world.push_back(std::make_shared<yz_rect>(0, 555, 0, 555, 555, green)) // left
        .push_back(std::make_shared<yz_rect>(0, 555, 0, 555, 0, red))      // right
        .push_back(std::make_shared<zx_rect>(0, 555, 0, 555, 0, white))    // bottom
        .push_back(std::make_shared<zx_rect>(0, 555, 0, 555, 555, white))  // up
        .push_back(std::make_shared<xy_rect>(0, 555, 0, 555, 555, white)); // front

    auto image_data = render(nx, ny, ns, cam, world);
    stbi_write_png("cornell_box.png", nx, ny, 3, (void *)&image_data[0], 0);
}

TEST_CASE("cornell_box_with_cuboid", "[cornell_box]")
{
    int nx{200};
    int ny{200};
    int ns{100};

    vec3 look_from{278, 278, -800};
    vec3 look_at{278, 278, 0};
    camera cam{look_from, look_at, {0, 1, 0}, degree_to_radian(40), float(nx) / ny};
    cam.lens_radius = 0;

    auto tex1 = std::make_shared<constant_texture>(vec3{15, 15, 15});
    auto tex_red = std::make_shared<constant_texture>(vec3{0.65, 0.05, 0.05});
    auto tex_white = std::make_shared<constant_texture>(vec3{0.73, 0.73, 0.73});
    auto tex_green = std::make_shared<constant_texture>(vec3{0.12, 0.45, 0.15});
    auto light = std::make_shared<diffuse_light>(tex1);
    auto red = std::make_shared<lambertian>(tex_red);
    auto white = std::make_shared<lambertian>(tex_white);
    auto green = std::make_shared<lambertian>(tex_green);

    hittable_vector world;
    world.push_back(std::make_shared<zx_rect>(213, 343, 227, 332, 554, light)) // top light
        .push_back(std::make_shared<yz_rect>(0, 555, 0, 555, 555, green))      // left
        .push_back(std::make_shared<yz_rect>(0, 555, 0, 555, 0, red))          // right
        .push_back(std::make_shared<zx_rect>(0, 555, 0, 555, 0, white))        // bottom
        .push_back(std::make_shared<zx_rect>(0, 555, 0, 555, 555, white))      // top
        .push_back(std::make_shared<xy_rect>(0, 555, 0, 555, 555, white));     // front
    world.push_back(std::make_shared<axis_aligned_cuboid>(vec3{130, 0, 65}, vec3{295, 165, 230}, white))
        .push_back(std::make_shared<axis_aligned_cuboid>(vec3{265, 0, 295}, vec3{430, 330, 460}, white));

    auto image_data = render(nx, ny, ns, cam, world);
    stbi_write_png("cornell_box_with_cuboid.png", nx, ny, 3, (void *)&image_data[0], 0);
}

TEST_CASE("cornell_box_with_cuboid_translate", "[cornell_box]")
{
    int nx{200};
    int ny{200};
    int ns{100};

    vec3 look_from{278, 278, -800};
    vec3 look_at{278, 278, 0};
    camera cam{look_from, look_at, {0, 1, 0}, degree_to_radian(40), float(nx) / ny};
    cam.lens_radius = 0;

    auto tex1 = std::make_shared<constant_texture>(vec3{15, 15, 15});
    auto tex_red = std::make_shared<constant_texture>(vec3{0.65, 0.05, 0.05});
    auto tex_white = std::make_shared<constant_texture>(vec3{0.73, 0.73, 0.73});
    auto tex_green = std::make_shared<constant_texture>(vec3{0.12, 0.45, 0.15});
    auto light = std::make_shared<diffuse_light>(tex1);
    auto red = std::make_shared<lambertian>(tex_red);
    auto white = std::make_shared<lambertian>(tex_white);
    auto green = std::make_shared<lambertian>(tex_green);

    hittable_vector world;
    world.push_back(std::make_shared<zx_rect>(213, 343, 227, 332, 554, light)) // top light
        .push_back(std::make_shared<yz_rect>(0, 555, 0, 555, 555, green))      // left
        .push_back(std::make_shared<yz_rect>(0, 555, 0, 555, 0, red))          // right
        .push_back(std::make_shared<zx_rect>(0, 555, 0, 555, 0, white))        // bottom
        .push_back(std::make_shared<zx_rect>(0, 555, 0, 555, 555, white))      // top
        .push_back(std::make_shared<xy_rect>(0, 555, 0, 555, 555, white));     // front
    world.push_back(std::make_shared<axis_aligned_cuboid>(vec3{130, 0, 65}, vec3{295, 165, 230}, white))
        .push_back(std::make_shared<axis_aligned_cuboid>(vec3{265, 0, 295}, vec3{430, 330, 460}, white))
        .push_back(std::make_shared<translate>(
            std::make_shared<axis_aligned_cuboid>(vec3{265, 0, 295}, vec3{430, 330, 460}, white),
            vec3{50, 50, 50}));

    auto image_data = render(nx, ny, ns, cam, world);
    stbi_write_png("cornell_box_with_cuboid_translate.png", nx, ny, 3, (void *)&image_data[0], 0);
}

TEST_CASE("cornell_box_with_cuboid_rotate", "[cornell_box]")
{
    int nx{200};
    int ny{200};
    int ns{100};

    vec3 look_from{278, 278, -800};
    vec3 look_at{278, 278, 0};
    camera cam{look_from, look_at, {0, 1, 0}, degree_to_radian(40), float(nx) / ny};
    cam.lens_radius = 0;

    auto tex1 = std::make_shared<constant_texture>(vec3{15, 15, 15});
    auto tex_red = std::make_shared<constant_texture>(vec3{0.65, 0.05, 0.05});
    auto tex_white = std::make_shared<constant_texture>(vec3{0.73, 0.73, 0.73});
    auto tex_green = std::make_shared<constant_texture>(vec3{0.12, 0.45, 0.15});
    auto light = std::make_shared<diffuse_light>(tex1);
    auto light_blue = std::make_shared<diffuse_light>(std::make_shared<constant_texture>(vec3(0, 0, 1)));
    auto red = std::make_shared<lambertian>(tex_red);
    auto white = std::make_shared<lambertian>(tex_white);
    auto green = std::make_shared<lambertian>(tex_green);
    auto glass = std::make_shared<dielectric>(1.5);

    hittable_vector world;
    world.push_back(std::make_shared<zx_rect>(213, 343, 227, 332, 554, light))     // top light
        .push_back(std::make_shared<yz_rect>(213, 343, 227, 332, 554, light_blue)) // left light
        .push_back(std::make_shared<yz_rect>(213, 343, 227, 332, 1, light_blue))   // right light
        .push_back(std::make_shared<yz_rect>(0, 555, 0, 555, 555, green))          // left
        .push_back(std::make_shared<yz_rect>(0, 555, 0, 555, 0, red))              // right
        .push_back(std::make_shared<zx_rect>(0, 555, 0, 555, 0, white))            // bottom
        .push_back(std::make_shared<zx_rect>(0, 555, 0, 555, 555, white))          // top
        .push_back(std::make_shared<xy_rect>(0, 555, 0, 555, 555, white));         // front
    {
        auto center = (vec3{130, 0, 65} + vec3{295, 165, 230}) / 2;
        world.push_back(
            std::make_shared<translate>(
                std::make_shared<rotate_y>(
                    std::make_shared<translate>(
                        std::make_shared<axis_aligned_cuboid>(vec3{130, 0, 65}, vec3{295, 165, 230}, glass),
                        -center),
                    degree_to_radian(60)),
                center));
    }
    {
        auto center = (vec3{265, 0, 295} + vec3{430, 330, 460}) / 2;
        world.push_back(
            std::make_shared<translate>(
                std::make_shared<rotate_y>(
                    std::make_shared<translate>(
                        std::make_shared<axis_aligned_cuboid>(vec3{265, 0, 295}, vec3{430, 330, 460}, white),
                        -center),
                    degree_to_radian(45)),
                center));
    }

    auto image_data = render(nx, ny, ns, cam, world);
    stbi_write_png("cornell_box_with_cuboid_rotate.png", nx, ny, 3, (void *)&image_data[0], 0);
}
