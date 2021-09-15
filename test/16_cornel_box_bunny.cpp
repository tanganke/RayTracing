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
#include "RayTracing/triangle.h"
#include <iostream>
#include <fstream>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <stb/stb_image_write.h>

using namespace ray_tracing;

TEST_CASE("cornell_box_bunny", "[cornell_box]")
{
    int nx{800};
    int ny{800};
    int ns{2000};

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

    auto bunny_green = std::make_shared<hittable_vector>();
    auto bunny_glass = std::make_shared<hittable_vector>();
    auto bunny_red = std::make_shared<hittable_vector>();
    {
        Assimp::Importer importer;
        auto scene = importer.ReadFile("data/bunny2.ply", aiProcess_Triangulate);
        auto transform = [](aiVector3D a_)
        {
            auto a = vec3{a_.x, a_.y, a_.z};
            static vec3 center{-0.03, 0.09, 0.01};
            a -= center;
            a *= 1000;
            a += 278;
            return a;
        };
        REQUIRE(scene != nullptr);
        REQUIRE(scene->HasMeshes());
        auto mesh = scene->mMeshes[0];
        for (int i = 0; i < mesh->mNumFaces; ++i)
        {
            auto face = mesh->mFaces[i];
            REQUIRE(face.mNumIndices == 3);
            auto a = mesh->mVertices[face.mIndices[0]];
            auto b = mesh->mVertices[face.mIndices[1]];
            auto c = mesh->mVertices[face.mIndices[2]];

            bunny_glass->push_back(std::make_shared<triangle>(
                transform(a), transform(b), transform(c),
                glass));
            bunny_red->push_back(std::make_shared<triangle>(
                transform(a), transform(b), transform(c),
                red));
            bunny_green->push_back(std::make_shared<triangle>(
                transform(a), transform(b), transform(c),
                green));
        }
    }
    float y_min;
    {
        aabb bbox;
        bunny_glass->bounding_box(bbox);
        y_min = bbox.lower_bound.y;
    }
    world.push_back(std::make_shared<translate>(bunny_glass, vec3{0, -y_min, 0}))
        .push_back(std::make_shared<translate>(bunny_red, vec3{150, -y_min, 0}))
        .push_back(std::make_shared<translate>(bunny_green, vec3{-150, -y_min, 0}));

    auto image_data = render(nx, ny, ns, cam, world);
    stbi_write_png("cornell_box_bunny.png", nx, ny, 3, (void *)&image_data[0], 0);
}
