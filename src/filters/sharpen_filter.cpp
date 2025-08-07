#include "sharpen_filter.h"
#include <opencv4/opencv2/opencv.hpp>

void SharpenFilter::configure(const FilterConfig& config) {
    auto it = config.parameters.find("strength");
    if (it != config.parameters.end()) {
        strength_ = it->second.get<double>();
    }
}

void SharpenFilter::apply(const cv::Mat& input, cv::Mat& output) {
    float strength = static_cast<float>(strength_);
    cv::Mat kernel = (cv::Mat_<float>(3, 3) << 0, -1 * strength, 0, -1 * strength, 1 + 4 * strength,
        -1 * strength, 0, -1 * strength, 0);
    cv::filter2D(input, output, -1, kernel);
}