#include <catch2/catch.hpp>
#include "RayTracing/progress_bar.h"
#include <chrono>

TEST_CASE("progress_bar")
{
    ray_tracing::ProgressBar bar("Rendering");
    while (true)
    {
        bar.tick();
        if (bar.is_completed())
            break;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
