#ifndef LANE_FINDING_BASIC_CPP_DISPLAY_H
#define LANE_FINDING_BASIC_CPP_DISPLAY_H

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui/highgui.hpp>

void display(const cv::Mat& image)
{
    namedWindow( "", cv::WINDOW_AUTOSIZE );
    imshow( "", image );
    cv::waitKey(25);
}

#endif //LANE_FINDING_BASIC_CPP_DISPLAY_H
