#include "progress_bar.h"

using namespace indicators;

namespace ray_tracing
{
    progress_bar::progress_bar(const std::string &prefix_text) : indicators::ProgressBar{
                                                                   option::BarWidth{50},
                                                                   option::Start{" ["},
                                                                   option::Fill{"█"},
                                                                   option::Lead{"█"},
                                                                   option::Remainder{"-"},
                                                                   option::End{"]"},
                                                                   option::PrefixText{prefix_text},
                                                                   option::ForegroundColor{Color::green},
                                                                   option::ShowElapsedTime{true},
                                                                   option::ShowRemainingTime{true},
                                                                   option::ShowPercentage{true},
                                                                   option::FontStyles{std::vector<FontStyle>{FontStyle::bold}}}
    {
    }

}