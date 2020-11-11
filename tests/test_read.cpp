#include "gtest/gtest.h"
#include "read.h"
#include "iostream"

TEST(read, read_images)
{
  std::string image_folder(PROJECT_ROOT);
  image_folder += "/data/test_images";
  auto images = read_images(image_folder);
  ASSERT_GT(images.size(), 0);
}

TEST(read, read_video_frames)
{
  std::string video_file(PROJECT_ROOT);
  video_file += "/data/test_videos/straight.mp4";
  auto frames = read_video_frames(video_file);
  ASSERT_GT(frames.size(), 0);
}