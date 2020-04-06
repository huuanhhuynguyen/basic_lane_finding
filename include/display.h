#ifndef BASIC_LANE_FINDING_CPP_DISPLAY_H
#define BASIC_LANE_FINDING_CPP_DISPLAY_H

#include <opencv2/highgui/highgui.hpp>

void display(const cv::Mat& image)
{
    namedWindow( "", cv::WINDOW_AUTOSIZE );
    imshow( "", image );
    cv::waitKey(25);
}

#endif //BASIC_LANE_FINDING_CPP_DISPLAY_H
