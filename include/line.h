#ifndef BASIC_LANE_FINDING_CPP_LINE_H
#define BASIC_LANE_FINDING_CPP_LINE_H

#include <vector>
#include <opencv2/core/matx.hpp>

/// This class calculates slope and bias of a line, given two separate points
struct Line {
    int x1, y1, x2, y2;

    constexpr float slope() const noexcept {
        return static_cast<float>(y2 - y1) / (static_cast<float>(x2 - x1) + _EPS);
    }

    constexpr float bias()  const noexcept {
        return static_cast<float>(y1) - slope()*static_cast<float>(x1);
    }

    explicit constexpr Line(int _x1, int _y1, int _x2, int _y2) :
            x1{_x1}, y1{_y1}, x2{_x2}, y2{_y2}
    {}

    explicit Line(float slope, float bias)
    {
        x1 = 0;
        y1 = static_cast<int>(slope * x1 + bias);
        x2 = 1000;
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

    constexpr int kBigNum = 1000;
    int x1 = cvRound(x0 + kBigNum*(-b));
    int y1 = cvRound(y0 + kBigNum*(a));
    int x2 = cvRound(x0 - kBigNum*(-b));
    int y2 = cvRound(y0 - kBigNum*(a));

    return Line(x1, y1, x2, y2);
}

/// returns a list of cartesian lines from hough lines. The latter come from cv::HoughLines.
std::vector<Line> cartesian_lines_from_hough_lines(const std::vector<cv::Vec2f>& lines)
{
    if (lines.empty()) {
        return {};
    }

    std::vector<Line> result;
    std::transform(lines.begin(), lines.end(), std::back_inserter(result), from_hough_line);
    return result;
}

#endif //BASIC_LANE_FINDING_CPP_LINE_H
