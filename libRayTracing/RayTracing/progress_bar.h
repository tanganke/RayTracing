#include <indicators/indicators.hpp>

namespace ray_tracing
{
    class ProgressBar : public indicators::ProgressBar
    {
    public:
        ProgressBar() : ProgressBar(std::string{""}) {}
        ProgressBar(const std::string &prefix_text);
    };
}
