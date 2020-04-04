#ifndef SELF_01_LANE_FINDING_BASIC_CPP_LINE_H
#define SELF_01_LANE_FINDING_BASIC_CPP_LINE_H

#include <utility>
#include <vector>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>

/// This class calculates slope and bias of a line, given two separate points
struct Line {
    int x1, y1, x2, y2;
    float slope() const noexcept { return float(y2 - y1) / (float(x2 - x1) + _EPS); }
    float bias()  const noexcept { return float(y1) - slope() + float(x1); }

    explicit Line(int _x1, int _y1, int _x2, int _y2) :
            x1{_x1}, y1{_y1}, x2{_x2}, y2{_y2}
    {}
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
    std::vector<Line> result;
    std::transform(lines.begin(), lines.end(), std::back_inserter(result), from_hough_line);
    return result;
}

void draw_lines_on_image(cv::Mat& dst, const std::vector<Line>& lines)
{
    for (const auto& line : lines)
    {
        cv::Point pt1 {line.x1, line.y1};
        cv::Point pt2 {line.x2, line.y2};
        cv::line(dst, pt1, pt2, cv::Scalar(0,0,255), 3, cv::LINE_AA);
    }
}

#endif //SELF_01_LANE_FINDING_BASIC_CPP_LINE_H
