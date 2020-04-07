#ifndef BASIC_LANE_FINDING_CPP_SAVE_H
#define BASIC_LANE_FINDING_CPP_SAVE_H

#include <iostream>
#include <opencv2/highgui/highgui.hpp>

/// save a video from "images" data, using the "input_video" properties
void save_video(const std::vector<cv::Mat>& images, const cv::VideoCapture& input_video)
{
    const int width = static_cast<int>(input_video.get(cv::CAP_PROP_FRAME_WIDTH));
    const int height = static_cast<int>(input_video.get(cv::CAP_PROP_FRAME_HEIGHT));
    const auto fps = input_video.get(cv::CAP_PROP_FPS);

    cv::VideoWriter output_video;
    output_video.open("out.mp4" , /* fourcc= */ -1, fps,
                      cv::Size(width, height), /* isColor= */ true);

    if (!output_video.isOpened()) {
        std::cerr << "Cannot open the video" << std::endl;
    }

    for(auto& image : images) {
        output_video.write(image);
    }
}

#endif //BASIC_LANE_FINDING_CPP_SAVE_H
