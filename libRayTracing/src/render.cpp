#include "render.h"

namespace ray_tracing
{
    std::vector<uint8_t> render(int nx, int ny, int ns, camera &cam, hittable &world)
    {
        progress_bar bar;
        bar.set_progress(0);
        std::vector<uint8_t> output_image(nx * ny * 3);
        auto output_it = output_image.begin();
        for (int j = ny - 1; j >= 0; j--)
        {
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
                auto &&ir = clamp<int>(int(255.99 * col[0]), 0, 255);
                auto &&ig = clamp<int>(int(255.99 * col[1]), 0, 255);
                auto &&ib = clamp<int>(int(255.99 * col[2]), 0, 255);
                *output_it++ = ir;
                *output_it++ = ig;
                *output_it++ = ib;
            }
            if (j % 10 == 0)
                bar.set_progress(static_cast<size_t>((ny - 1 - j) * 100 / ny));
        }
        bar.mark_as_completed();
        return output_image;
    }
}