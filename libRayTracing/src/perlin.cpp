#include "perlin.h"
#include "random.h"
#include <algorithm>
#include <numeric>

namespace ray_tracing
{
    static std::vector<float> perlin_generate()
    {
        std::vector<float> p(256);
        for (int i = 0; i < 256; ++i)
            p[i] = drand48();
        return p;
    }

    static std::vector<vec3> perlin_generate_vec3()
    {
        std::vector<vec3> p(256);
        std::generate(p.begin(), p.end(), []()
                      { return unit_vector(random_vec3(-1, 1)); });
        return p;
    }

    void permute(int *p, int n)
    {
        for (int i = n - 1; i > 0; i--)
        {
            int target = int(drand48() * (i + 1));
            std::swap(p[i], p[target]);
        }
        return;
    }

    static std::vector<int> perlin_generate_perm()
    {
        std::vector<int> p(256);
        std::iota(p.begin(), p.end(), 0);
        permute(&p[0], 256);
        return p;
    }

    static std::vector<float>
        ranfloat{perlin_generate()};
    static std::vector<vec3>
        ranvec{perlin_generate_vec3()};
    static std::vector<int>
        perm_x{perlin_generate_perm()},
        perm_y{perlin_generate_perm()},
        perm_z{perlin_generate_perm()};

    float perlin_noise(const vec3 &p)
    {
        float u = p.x - std::floor(p.x);
        float v = p.y - std::floor(p.y);
        float w = p.z - std::floor(p.z);

        int i = int(4 * p.x) & 255;
        int j = int(4 * p.y) & 255;
        int k = int(4 * p.z) & 255;
        return ranfloat[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
    }

    float perlin_noise_trilinear_interp(const vec3 &p)
    {
        static const auto trilinear_interp = [](float c[2][2][2], float u, float v, float w) -> float
        {
            float accum = 0;
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++)
                    for (int k = 0; k < 2; k++)
                        accum += (i * u + (1 - i) * (1 - u)) *
                                 (j * v + (1 - j) * (1 - v)) *
                                 (k * w + (1 - k) * (1 - w)) * c[i][j][k];
            return accum;
        };

        float u = p.x - std::floor(p.x);
        float v = p.y - std::floor(p.y);
        float w = p.z - std::floor(p.z);

        int i = std::floor(p.x);
        int j = std::floor(p.y);
        int k = std::floor(p.z);

        float c[2][2][2];
        for (int di = 0; di < 2; di++)
            for (int dj = 0; dj < 2; dj++)
                for (int dk = 0; dk < 2; dk++)
                    c[di][dj][dk] = ranfloat[perm_x[(i + di) & 255] ^ perm_y[(j + dj) & 255] ^ perm_z[(k + dk) & 255]];

        return trilinear_interp(c, u, v, w);
    }

    float perlin_noise_hermite_cubic(const vec3 &p)
    {
        static const auto trilinear_interp = [](float c[2][2][2], float u, float v, float w) -> float
        {
            float accum = 0;
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++)
                    for (int k = 0; k < 2; k++)
                        accum += (i * u + (1 - i) * (1 - u)) *
                                 (j * v + (1 - j) * (1 - v)) *
                                 (k * w + (1 - k) * (1 - w)) * c[i][j][k];
            return accum;
        };

        float u = p.x - std::floor(p.x);
        float v = p.y - std::floor(p.y);
        float w = p.z - std::floor(p.z);

        u = u * u * (3 - 2 * u);
        v = v * v * (3 - 2 * v);
        w = w * w * (3 - 2 * w);

        int i = std::floor(p.x);
        int j = std::floor(p.y);
        int k = std::floor(p.z);

        float c[2][2][2];
        for (int di = 0; di < 2; di++)
            for (int dj = 0; dj < 2; dj++)
                for (int dk = 0; dk < 2; dk++)
                    c[di][dj][dk] = ranfloat[perm_x[(i + di) & 255] ^ perm_y[(j + dj) & 255] ^ perm_z[(k + dk) & 255]];

        return trilinear_interp(c, u, v, w);
    }

    float perlin_noise_hermite_cubic_vec(const vec3 &p)
    {
        static const auto trilinear_interp = [](vec3 c[2][2][2], float u, float v, float w) -> float
        {
            float uu = u * u * (3 - 2 * u);
            float vv = v * v * (3 - 2 * v);
            float ww = w * w * (3 - 2 * w);
            float accum{};

            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++)
                    for (int k = 0; k < 2; k++)
                    {
                        vec3 weight_v{u - i, v - j, w - k};
                        accum += (i * u + (1 - i) * (1 - u)) *
                                 (j * v + (1 - j) * (1 - v)) *
                                 (k * w + (1 - k) * (1 - w)) * dot(c[i][j][k], weight_v);
                    }
            return accum;
        };

        float u = p.x - std::floor(p.x);
        float v = p.y - std::floor(p.y);
        float w = p.z - std::floor(p.z);

        int i = std::floor(p.x);
        int j = std::floor(p.y);
        int k = std::floor(p.z);

        vec3 c[2][2][2];
        for (int di = 0; di < 2; di++)
            for (int dj = 0; dj < 2; dj++)
                for (int dk = 0; dk < 2; dk++)
                    c[di][dj][dk] = ranvec[perm_x[(i + di) & 255] ^ perm_y[(j + dj) & 255] ^ perm_z[(k + dk) & 255]];

        return trilinear_interp(c, u, v, w);
    }
}