#pragma once
#include "hittable.h"
#include "camera.h"
#include "color.h"
#include "progress_bar.h"

namespace ray_tracing
{
    std::vector<uint8_t> render(int nx, int ny, int ns, camera &cam, hittable &world);
}