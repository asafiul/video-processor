#include "edge_detect_filter.h"
#include <opencv4/opencv2/opencv.hpp>

void EdgeDetectFilter::configure(const FilterConfig& config) {
    auto it = config.parameters.find("low_threshold");
    if (it != config.parameters.end()) {
        low_threshold_ = it->second.get<double>();
    }

    it = config.parameters.find("high_threshold");
    if (it != config.parameters.end()) {
        high_threshold_ = it->second.get<double>();
    }
}

void EdgeDetectFilter::apply(const cv::Mat& input, cv::Mat& output) {
    cv::Mat gray;
    if (input.channels() == 3) {
        cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    } else {
        gray = input;
    }

    cv::Canny(gray, output, low_threshold_, high_threshold_);
}