//
// Created by ngh7rng on 04.04.20.
//

#ifndef SELF_01_LANE_FINDING_BASIC_CPP_FILTER_H
#define SELF_01_LANE_FINDING_BASIC_CPP_FILTER_H

#include "line.h"

std::vector<Line> filter_slope(const std::vector<Line>& candidate_lines)
{
    if (candidate_lines.empty())
    {
        return candidate_lines;
    }

    std::vector<Line> lines;
    for (const auto& line: candidate_lines)
    {
        const auto abs_slope = abs(line.slope());
        if(0.5 < abs_slope && abs_slope < 2.0)
        {
            lines.push_back(line);
        }
    }

    return lines;
}


#endif //SELF_01_LANE_FINDING_BASIC_CPP_FILTER_H
