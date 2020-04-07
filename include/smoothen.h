#ifndef BASIC_LANE_FINDING_CPP_SMOOTHEN_H
#define BASIC_LANE_FINDING_CPP_SMOOTHEN_H

#include <deque>
#include <numeric>
#include "line.h"

/// Calculates the moving average value.
/// Example:
///     MovAvg<float> mov_avg{3}; // window size = 3
///     mov_avg.update(3);  // returns 3
///     mov_avg.update(5);  // returns (3+5)/2 = 4
///     mov_avg.update(10); // returns (3+5+10)/3 = 6
///     mov_avg.update(-2); // returns (5+10-2)/3 = 4.333
template <typename T>
class MovAvg {
public:
    explicit constexpr MovAvg(unsigned int window = 5) : _kWindow{window} {}

    /// update history and return the moving-averaged value
    constexpr T update(const T& number) const noexcept
    {
        if (_prevs.size() >= _kWindow)
        {
            _prevs.pop_front();
        }
        _prevs.push_back(number);
        const auto sum = std::accumulate(_prevs.begin(), _prevs.end(), 0.0);
        const auto mean = sum / _prevs.size();
        return static_cast<T>(mean);
    }

private:
    mutable std::deque<T> _prevs;
    const unsigned int _kWindow;
};

/// Calculates moving-averaged line (i.e. moving averaged slope and bias).
/// Example:
///    LineMovAvg mov_avg{2};  // window size = 2
///    Line line{0.5, 2};      // slope = 0.5, bias = 2
///    mov_avg.update(line);   // returns a line with slope 0.5 and bias 2.0
///    mov_avg.update(Line{-0.5, 3}); // returns slope 0.0 and bias 2.5
///    mov_avg.update(Line{2.5, -5}); // returns slope 1.0 and bias -1
class LineMovAvg {
public:
    explicit constexpr LineMovAvg(unsigned int window = 5) :
        _kWindow{window}, _slope_mov_avg{window}, _bias_mov_avg{window} {}

    /// update history and return the moving-averaged line
    Line update(const Line& line) const noexcept
    {
        const auto slope = _slope_mov_avg.update(line.slope());
        const auto bias = _bias_mov_avg.update(line.bias());
        return Line{slope, bias};
    }

private:
    MovAvg<float> _slope_mov_avg;
    MovAvg<float> _bias_mov_avg;
    const unsigned int _kWindow;
};

#endif //BASIC_LANE_FINDING_CPP_SMOOTHEN_H
