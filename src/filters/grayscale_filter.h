#pragma once
#include "filter_base.h"

class GrayscaleFilter : public FilterBase {
public:
    void apply(const cv::Mat& input, cv::Mat& output) override;
    bool isColor() const override { return false; }
    std::string getName() const override { return "grayscale"; }
    void configure(const FilterConfig& config) override { }
};