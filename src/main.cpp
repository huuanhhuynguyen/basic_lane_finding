#include <opencv2/imgproc.hpp>

#include "read.h"
#include "display.h"
#include "roi.h"
#include "filter.h"
#include "median.h"
#include "smoothen.h"
#include "save.h"

int main() {
    // read images/videos from the given path and return an image list
    std::string filepath = "../data/test_videos/corner.mp4";
    //auto images = read_images(std::string("../data/test_images"));
    auto images = read_video_frames(filepath);

    LineMovAvg right_mov_avg, left_mov_avg;
    // for every image in images
    for (auto& image : images)
    {
        // apply Gaussian Blur on image
        cv::Mat blur_image;
        cv::GaussianBlur(image, blur_image, cv::Size(17, 17), 0);

        // apply canny on image
        cv::Mat canny_image;
        cv::Canny(blur_image, canny_image, 50, 80);

        // apply region of interest
        cv::Mat roi_image = mask_roi(canny_image);

        // apply Hough line detection
        std::vector<cv::Vec2f> hough_lines;
        cv::HoughLines(roi_image, hough_lines, 1, CV_PI / 180,30);

        // transform hough lines into cartesian lines
        const auto candidate_lines = cartesian_lines_from_hough_lines(hough_lines);

        // filter out candidate (cartesian) lines and get final detected lines
        const auto final_lines = filter_slope(candidate_lines);

        // get median lines
        const auto pos_lines = get_lines_with_positive_slope(final_lines);
        const auto neg_lines = get_lines_with_negative_slope(final_lines);

        if(!pos_lines.empty() && !neg_lines.empty())
        {
            auto right = get_median_line(pos_lines);
            auto left = get_median_line(neg_lines);

            // time-smoothening
            right = right_mov_avg.update(right);
            left = left_mov_avg.update(left);

            // draw the final detection lines
            draw_lines_on_image(image, {left, right});
        }

        // display the image with the final detection lines
        display(image);
    }

    // uncomment the following save the video
    //const cv::VideoCapture input_video(filepath);
    //save_video(images, input_video);

    return 0;
}

