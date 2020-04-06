#ifndef BASIC_LANE_FINDING_CPP_DRAW_H
#define BASIC_LANE_FINDING_CPP_DRAW_H

#include "line.h"
#include "roi.h"

/// Adjust two points of the line so that they two are visible in the display window
void _adjust_line_visible(Line& line, int img_h, int img_w)
{
    const auto slope = line.slope() + 0.00001;  // prevents division by 0
    const auto bias = line.bias();
    cv::Point pt_in_1, pt_in_2;  // points on the line that should be visible
    {
        int x = 0;
        int y = static_cast<int>(slope * x + bias);
        if (y < 0)
        {
            x = img_w;
            y = static_cast<int>(slope * x + bias);
        }
        pt_in_1 = cv::Point{x, y};
    }
    {
        int y = 0;
        int x = static_cast<int>((y - bias) / slope);
        if (x < 0)
        {
            y = img_h;
            x = static_cast<int>((y - bias) / slope);
        }
        pt_in_2 = cv::Point{x, y};
    }

    line = Line{pt_in_1.x, pt_in_1.y, pt_in_2.x, pt_in_2.y};
}

void draw_lines_on_image(cv::Mat& dst, const std::vector<Line>& lines)
{
    auto image_with_line = dst.clone();
    for (auto line : lines)
    {
        _adjust_line_visible(line, dst.rows, dst.cols);
        cv::Point pt1 {line.x1, line.y1};
        cv::Point pt2 {line.x2, line.y2};
        cv::line(image_with_line, pt1, pt2,cv::Scalar(255, 0, 0), 5, cv::LINE_AA);
    }

    // blend image
    image_with_line = mask_roi(image_with_line);
    cv::addWeighted(image_with_line, 0.7, dst, 0.3, 0.0, dst);
}

#endif //BASIC_LANE_FINDING_CPP_DRAW_H
