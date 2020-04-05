#include <opencv2/imgproc.hpp>

#include "read.h"
#include "display.h"
#include "roi.h"
#include "filter.h"
#include "median.h"

int main() {
    // read images/videos from the given path and return a list
    //auto images = read_images(std::string("../data/test_images"));
    auto images = read_video_frames(std::string("../data/test_videos/solidWhiteRight.mp4"));

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
        const auto right = get_median_line(pos_lines);
        const auto left = get_median_line(neg_lines);

        // draw the final lines
        draw_lines_on_image(image, {left, right});

        // time-smoothening

        // display the image with the final lines
        display(image);

        // save the visualized image in the output path

    }
    return 0;
}
