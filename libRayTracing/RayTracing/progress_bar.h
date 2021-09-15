#pragma once
#include <indicators/indicators.hpp>

namespace ray_tracing
{
    class progress_bar : public indicators::ProgressBar
    {
    public:
        progress_bar() : progress_bar(std::string{""}) {}
        progress_bar(const std::string &prefix_text);
    };
}
