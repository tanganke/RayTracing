#include <catch2/catch.hpp>
#include <stb/stb_image_write.h>
#include <RayTracing/vec.h>

using namespace ray_tracing;

TEST_CASE("write_image")
{
    uvec3 img[2][2] = {uvec3{255, 0, 0}};
    stbi_write_bmp("test.bmp", 2, 2, 3, img);
}