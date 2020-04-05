#ifndef SELF_01_LANE_FINDING_BASIC_CPP_MEDIAN_H
#define SELF_01_LANE_FINDING_BASIC_CPP_MEDIAN_H

#include <vector>
#include "line.h"

template <typename T>
T _median(std::vector<T> arr)
{
    std::sort(arr.begin(), arr.end());
    int mid{arr.size()/2};
    return arr[mid];
}

Line get_median_line(const std::vector<Line>& lines)
{
    // get list of slopes and biases
    std::vector<float> slopes, biases;
    std::transform(lines.begin(), lines.end(), std::back_inserter(slopes),
            [](const auto& line){ return line.slope(); });
    std::transform(lines.begin(), lines.end(), std::back_inserter(biases),
                   [](const auto& line){ return line.bias(); });

    // get the median slope and bias
    const auto median_slope = _median(slopes);
    const auto median_bias = _median(biases);

    // return the line with the median slope and bias
    int x1 = 0;
    int y1 = static_cast<int>(median_bias);
    int x2 = - static_cast<int>(median_bias/median_slope);
    int y2 = 0;
    return Line{x1, y1, x2, y2};
}

#endif //SELF_01_LANE_FINDING_BASIC_CPP_MEDIAN_H
