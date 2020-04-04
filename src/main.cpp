#include "opencv2/imgproc.hpp"

#include "read.h"
#include "display.h"

int main() {
    // read images from the given path and return a list
    auto images = read_images(std::string("../data/test_images"));

    // for every image in images
    for(const auto& image : images)
    {
        // apply Gaussian Blur on image
        cv::Mat blur_image {};
        cv::GaussianBlur(image, blur_image, cv::Size(17, 17), 0);

        // apply canny on image
        cv::Mat canny_image {};
        cv::Canny(blur_image, canny_image, 50, 80);

        // apply Hough transform
        std::vector<cv::Vec2f> lines;
        cv::HoughLines(canny_image, lines, 2, CV_PI/180, 1, 0, 0 );

        // apply Hough line detection, get line candidates
        // get final lines from the candidates
        // filter the slope
        // filter region of interest
        // further filtering
        // create a copy of the original image
        // visualize the final lines on the copy image
        // save the visualized image in the output path

        display(canny_image);
    }

    return 0;
}
