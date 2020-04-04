#ifndef SELF_01_LANE_FINDING_BASIC_CPP_READ_H
#define SELF_01_LANE_FINDING_BASIC_CPP_READ_H

#include <vector>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <boost/filesystem.hpp>

/// list all files in a directory
/// source: www.martinbroadhurst.com/list-the-files-in-a-directory-in-c.html
std::vector<std::string> list_dir(const std::string& directory)
{
    std::vector<std::string> result;

    boost::filesystem::path p(directory);
    boost::filesystem::directory_iterator start(p);
    boost::filesystem::directory_iterator end;

    auto path_leaf_string = [](const auto& entry){ return entry.path().leaf().string(); };
    std::transform(start, end, std::back_inserter(result), path_leaf_string);

    return result;
}

/// Read all files in a directory and return a list of images
std::vector<cv::Mat> read_images(const std::string& directory)
{
    auto filenames = list_dir(directory);

    std::vector<cv::Mat> images;

    auto img_read = [](const auto& path){ return cv::imread(path); };
    std::transform(filenames.begin(), filenames.end(), std::back_inserter(images), img_read);

    return images;
}


#endif //SELF_01_LANE_FINDING_BASIC_CPP_READ_H