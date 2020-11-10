#include "gtest/gtest.h"
#include "read.h"

TEST(read, read_images)
{
  auto images = read_images("../../data/test_images");
  ASSERT_GT(images.size(), 0);
}

TEST(read, read_video_frames)
{
  auto frames = read_video_frames("../../data/test_videos/straight.mp4");
  ASSERT_GT(frames.size(), 0);
}