#include <opencv2/imgproc.hpp>

#include "read.h"
#include "display.h"
#include "roi.h"
#include "filter.h"

int main() {
    // read images from the given path and return a list
    auto images = read_images(std::string("../data/test_images"));

    // for every image in images
    for (const auto& image : images)
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
        cv::HoughLines(roi_image, hough_lines, 2, CV_PI/180, 1, 0, 0 );

        // transform hough lines into cartesian lines
        auto candidate_lines = cartesian_lines_from_hough_lines(hough_lines);

        // filter out candidate (cartesian) lines and get final detected lines
        auto final_lines = filter_slope(candidate_lines);

        // draw the final lines
        auto visualized_image = image;
        draw_lines_on_image(visualized_image, final_lines);

        // display the image with the final lines
        display(visualized_image);

        // save the visualized image in the output path

    }
    return 0;
}
