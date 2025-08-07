#include <gtest/gtest.h>
#include "opencv4/opencv2/opencv.hpp"
#include "../src/video_processor.h"
#include "../src/filters/grayscale_filter.h"

TEST(VideoProcessorTest, ApplyGrayscaleFilter) {
    cv::Mat testImage(100, 100, CV_8UC3, cv::Scalar(0, 100, 200));
    cv::imwrite("../data/test_input.jpg", testImage);

    VideoProcessor processor;
    GrayscaleFilter filter;

    cv::Mat output;
    filter.apply(testImage, output);

    ASSERT_EQ(output.channels(), 1);
    ASSERT_EQ(output.rows, 100);
    ASSERT_EQ(output.cols, 100);
}
