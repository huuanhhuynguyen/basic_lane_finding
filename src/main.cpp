#include "read.h"

int main() {
    // read images from the given path and return a list
    auto images = read_images(std::string("../data/test_images"));

    // for every image in images
    for(const auto& image : images)
    {
        // create a copy of the original image
        // convert image into RGB
        // apply Gaussian Blur on image
        // apply canny on image
        // apply Hough transform
        // apply Hough line detection, get line candidates
        // get final lines from the candidates
        // filter the slope
        // filter region of interest
        // further filtering
        // create a copy of the original image
        // visualize the final lines on the copy image
        // save the visualized image in the output path
    }

    return 0;
}
