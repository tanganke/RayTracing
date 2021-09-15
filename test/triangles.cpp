#include "catch2/catch.hpp"
#include "RayTracing/render.h"
#include "RayTracing/light.h"
#include "RayTracing/triangle.h"
#include "stb/stb_image_write.h"
#include "time.h"

using namespace ray_tracing;

TEST_CASE("trangle")
{
    int nx{100};
    int ny{100};
    int ns{50};

    vec3 look_from{5, 0, 5};
    vec3 look_at{0, 0, 0};
    camera cam{look_from, look_at, {0, 1, 0}, degree_to_radian(40), float(nx) / ny};
    cam.lens_radius = 0;

    auto tex1 = std::make_shared<constant_texture>(vec3{15, 15, 15});
    auto light = std::make_shared<lambertian>(tex1);

    srand48(time(nullptr));
    triangle tri{random_vec3_in_unit_sphere(), random_vec3_in_unit_sphere(), random_vec3_in_unit_sphere(), light};

    auto image_data = render(nx, ny, ns, cam, tri);
    stbi_write_png("trangle.png", nx, ny, 3, (void *)&image_data[0], 0);
}