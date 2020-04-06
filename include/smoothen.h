#ifndef LANE_FINDING_BASIC_CPP_SMOOTHEN_H
#define LANE_FINDING_BASIC_CPP_SMOOTHEN_H

#include <deque>
#include <numeric>
#include "line.h"
#include "median.h"

template <typename T>
class MovAvg
{
public:
    explicit constexpr MovAvg(unsigned int _window = 5) : kWindow{_window} {}

    /// return the moving average value
    constexpr T update(const T& number) const noexcept {
        if (prevs.size() >= kWindow)
        {
            prevs.pop_front();
        }
        prevs.push_back(number);
        const auto sum = std::accumulate(prevs.begin(), prevs.end(), 0.0);
        const auto mean = sum / prevs.size();
        return static_cast<T>(mean);
    }

private:
    mutable std::deque<T> prevs;
    const unsigned int kWindow;
};

class LineMovAvg
{
public:
    explicit constexpr LineMovAvg(unsigned int _window = 5) :
        kWindow{_window}, slope_mov_avg{_window}, bias_mov_avg{_window}
    {}

    /// return the moving average line
    Line update(const Line& line) const noexcept {
        const auto slope = slope_mov_avg.update(line.slope());
        const auto bias = bias_mov_avg.update(line.bias());
        return Line{slope, bias};
    }

private:
    MovAvg<float> slope_mov_avg;
    MovAvg<float> bias_mov_avg;
    const unsigned int kWindow;
};

#endif //LANE_FINDING_BASIC_CPP_SMOOTHEN_H
