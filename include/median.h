#ifndef SELF_01_LANE_FINDING_BASIC_CPP_MEDIAN_H
#define SELF_01_LANE_FINDING_BASIC_CPP_MEDIAN_H

#include <vector>
#include "line.h"

template <typename T,
          template <typename ELEM, typename = std::allocator<ELEM>> class CONTAINER>
T median(CONTAINER<T> nums)
{
    std::sort(nums.begin(), nums.end());
    int mid{nums.size()/2};
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

#endif //SELF_01_LANE_FINDING_BASIC_CPP_MEDIAN_H
