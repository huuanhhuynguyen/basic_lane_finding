#ifndef SELF_01_LANE_FINDING_BASIC_CPP_ROI_H
#define SELF_01_LANE_FINDING_BASIC_CPP_ROI_H

#include <opencv2/imgproc.hpp>

cv::Mat mask_roi(const cv::Mat& src)
{
    auto img_h = src.rows;
    auto img_w = src.cols;

    cv::Rect ROI{0, int(img_h/2), img_w, int(img_h/2)};

    // get mask
    cv::Mat mask(src.size(), src.type(), cv::Scalar::all(0));
    mask(ROI).setTo(cv::Scalar::all(255));

    // apply mask
    cv::Mat result;
    cv::bitwise_and(src, mask, result);
    return result;
}

#endif //SELF_01_LANE_FINDING_BASIC_CPP_ROI_H
