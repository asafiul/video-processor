#include "blur_filter.h"
#include <opencv4/opencv2/opencv.hpp>

void BlurFilter::configure(const FilterConfig& config) {
    auto it = config.parameters.find("kernel_size");
    if (it != config.parameters.end()) {
        kernel_size_ = it->second.get<int>();
    }

    it = config.parameters.find("sigma");
    if (it != config.parameters.end()) {
        sigma_ = it->second.get<double>();
    }
}

void BlurFilter::apply(const cv::Mat& input, cv::Mat& output) {
    cv::Size kernelSize(kernel_size_, kernel_size_);
    cv::GaussianBlur(input, output, kernelSize, sigma_);
}