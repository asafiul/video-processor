#pragma once
#include "filter_base.h"

class SharpenFilter : public FilterBase {
public:
    SharpenFilter()
        : strength_(1.0) { }

    void apply(const cv::Mat& input, cv::Mat& output) override;
    bool isColor() const override { return true; }
    std::string getName() const override { return "sharpen"; }
    void configure(const FilterConfig& config) override;

private:
    double strength_;
};