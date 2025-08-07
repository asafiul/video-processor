#pragma once
#include "video_filter_service/config.h"
#include <nlohmann/json.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <string>

class FilterBase {
public:
    virtual void apply(const cv::Mat& input, cv::Mat& output) = 0;
    virtual bool isColor() const = 0;
    virtual std::string getName() const = 0;
    virtual void configure(const FilterConfig& config) { }

    virtual ~FilterBase() = default;
};