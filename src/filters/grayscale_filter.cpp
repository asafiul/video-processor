#include "grayscale_filter.h"
#include <opencv4/opencv2/opencv.hpp>

void GrayscaleFilter::apply(const cv::Mat& input, cv::Mat& output) {
    if (input.channels() == 3) {
        cv::cvtColor(input, output, cv::COLOR_BGR2GRAY);
    } else {
        output = input.clone();
    }
}