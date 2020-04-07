#ifndef BASIC_LANE_FINDING_CPP_ROI_H
#define BASIC_LANE_FINDING_CPP_ROI_H

#include <opencv2/imgproc.hpp>

cv::Mat mask_roi(const cv::Mat& src)
{
    const auto img_h = src.rows;
    const auto img_w = src.cols;

    // ROI: x0, y0, width, height
    cv::Rect ROI{0, int(img_h * 0.6), img_w, int(img_h * 0.4)};

    // get mask
    cv::Mat mask(src.size(), src.type(), cv::Scalar::all(0));
    mask(ROI).setTo(cv::Scalar::all(255));

    // apply mask
    cv::Mat result;
    cv::bitwise_and(src, mask, result);
    return result;
}

#endif //BASIC_LANE_FINDING_CPP_ROI_H
