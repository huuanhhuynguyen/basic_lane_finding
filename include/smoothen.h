#ifndef SELF_01_LANE_FINDING_BASIC_CPP_SMOOTHEN_H
#define SELF_01_LANE_FINDING_BASIC_CPP_SMOOTHEN_H

#include <deque>
#include <numeric>
#include "line.h"

template <typename T>
class MovAvg
{
public:
    explicit MovAvg(unsigned int _window = 3) : kWindow{_window} {}

    /// return the moving average value
    T update(T&& number) const noexcept {
        if (prevs.size() >= kWindow)
        {
            prevs.pop_front();
        }
        prevs.push_back(std::forward<T>(number));
        auto sum = std::accumulate(prevs.begin(), prevs.end(), 0.0);
        auto mean = sum / prevs.size();
        return static_cast<T>(mean);
    }

private:
    mutable std::deque<T> prevs;
    const unsigned int kWindow;
};

class LineMovAvg
{
public:
    explicit LineMovAvg(unsigned int _window = 3) :
        kWindow{_window}, slope_mov_avg{_window}, bias_mov_avg{_window}
    {}

    /// return the moving average line
    Line update(const Line& line) const noexcept {
        auto slope = slope_mov_avg.update(line.slope());
        auto bias = bias_mov_avg.update(line.bias());
        return Line{slope, bias};
    }

private:
    MovAvg<float> slope_mov_avg;
    MovAvg<float> bias_mov_avg;
    const unsigned int kWindow;
};

#endif //SELF_01_LANE_FINDING_BASIC_CPP_SMOOTHEN_H