#include <catch2/catch.hpp>
#include "RayTracing/sphere.h"
#include <iostream>

using namespace ray_tracing;

TEST_CASE("sphere_aabb", "[aabb]")
{
    sphere s{vec3{1, 1, 1}, 2};
    aabb s_bbox;
    hittable &h = s;
    REQUIRE(s.bounding_box(s_bbox));
    std::cout << s_bbox << std::endl;
    REQUIRE(h.bounding_box(s_bbox));
    std::cout << s_bbox << std::endl;
}