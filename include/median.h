#ifndef BASIC_LANE_FINDING_CPP_MEDIAN_H
#define BASIC_LANE_FINDING_CPP_MEDIAN_H

#include <iostream>
#include <vector>
#include "line.h"

template <typename T,
          template <typename ELEM, typename = std::allocator<ELEM>> class CONTAINER>
T median(CONTAINER<T> nums)
{
    if (nums.empty()) {
        std::cerr << "nums is empty in the function median." << std::endl;
    }

    std::sort(nums.begin(), nums.end());
    int mid( nums.size()/2 );
    return nums[mid];
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
    const auto median_slope = median(slopes);
    const auto median_bias = median(biases);

    return Line{median_slope, median_bias};
}

#endif //BASIC_LANE_FINDING_CPP_MEDIAN_H
