#ifndef SELF_01_LANE_FINDING_BASIC_CPP_SAVE_H
#define SELF_01_LANE_FINDING_BASIC_CPP_SAVE_H

#include <opencv2/highgui/highgui.hpp>

/// save a video from "images" data, using the "input_video" properties
void save_video(const std::vector<cv::Mat>& images, const cv::VideoCapture& input_video)
{
    const int width = static_cast<int>(input_video.get(cv::CAP_PROP_FRAME_WIDTH));
    const int height = static_cast<int>(input_video.get(cv::CAP_PROP_FRAME_HEIGHT));
    const auto fps = input_video.get(cv::CAP_PROP_FPS);

    cv::VideoWriter output_video;
    output_video.open("out.mp4" ,-1, fps,cv::Size(width, height), true);

    if(!output_video.isOpened())
    {
        std::cerr << "Cannot open the video" << std::endl;
    }

    for(auto& image : images)
    {
        output_video.write(image);
    }
    output_video.release();
}

#endif //SELF_01_LANE_FINDING_BASIC_CPP_SAVE_H
