#ifndef SELF_01_LANE_FINDING_BASIC_CPP_LINE_H
#define SELF_01_LANE_FINDING_BASIC_CPP_LINE_H

#include <utility>
#include <vector>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>
#include "roi.h"

/// This class calculates slope and bias of a line, given two separate points
struct Line {
    int x1, y1, x2, y2;

    constexpr float slope() const noexcept {
        return static_cast<float>(y2 - y1) / (static_cast<float>(x2 - x1) + _EPS);
    }

    constexpr float bias()  const noexcept { return static_cast<float>(y1) - slope()*static_cast<float>(x1); }

    explicit Line(int _x1, int _y1, int _x2, int _y2) :
            x1{_x1}, y1{_y1}, x2{_x2}, y2{_y2}
    {}

    explicit Line(float slope, float bias)
    {
        x1 = 0;
        y1 = static_cast<int>(slope * x1 + bias);
        x2 = 10;
        y2 = static_cast<int>(slope * x2 + bias);
    }
private:
    static constexpr float _EPS = 0.000001;  // prevents zero division
};

Line from_hough_line(const cv::Vec2f& line)
{
    float rho = line[0], theta = line[1];
    float a = cos(theta), b = sin(theta);
    float x0 = a * rho, y0 = b * rho;

    const int kBigNum = 1000;
    int x1 = cvRound(x0 + kBigNum*(-b));
    int y1 = cvRound(y0 + kBigNum*(a));
    int x2 = cvRound(x0 - kBigNum*(-b));
    int y2 = cvRound(y0 - kBigNum*(a));

    return Line(x1, y1, x2, y2);
}

/// return a list of cartesian lines from hough lines. The latter come from cv::HoughLines.
std::vector<Line> cartesian_lines_from_hough_lines(const std::vector<cv::Vec2f>& lines)
{
    if (lines.empty())
    {
        return {};
    }

    std::vector<Line> result;
    std::transform(lines.begin(), lines.end(), std::back_inserter(result), from_hough_line);
    return result;
}

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

#endif //SELF_01_LANE_FINDING_BASIC_CPP_LINE_H
