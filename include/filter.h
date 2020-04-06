#ifndef LANE_FINDING_BASIC_CPP_FILTER_H
#define LANE_FINDING_BASIC_CPP_FILTER_H

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

std::vector<Line> get_lines_with_positive_slope(const std::vector<Line>& lines)
{
    if (lines.empty())
    {
        return {};
    }

    std::vector<Line> pos_lines;
    auto is_slope_pos = [](const auto& line) { return line.slope() > 0; };
    std::copy_if(lines.begin(), lines.end(), std::back_inserter(pos_lines), is_slope_pos);
    return pos_lines;
}

std::vector<Line> get_lines_with_negative_slope(const std::vector<Line>& lines)
{
    if (lines.empty())
    {
        return {};
    }

    std::vector<Line> pos_lines;
    auto is_slope_neg = [](const auto& line) { return line.slope() < 0; };
    std::copy_if(lines.begin(), lines.end(), std::back_inserter(pos_lines), is_slope_neg);
    return pos_lines;
}

#endif //LANE_FINDING_BASIC_CPP_FILTER_H
