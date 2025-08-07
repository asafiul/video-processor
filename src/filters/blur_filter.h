#pragma once
#include "filter_base.h"

class BlurFilter : public FilterBase {
public:
    BlurFilter()
        : kernel_size_(15)
        , sigma_(0.0) { }

    void apply(const cv::Mat& input, cv::Mat& output) override;
    bool isColor() const override { return true; }
    std::string getName() const override { return "blur"; }
    void configure(const FilterConfig& config) override;

private:
    int kernel_size_;
    double sigma_;
};