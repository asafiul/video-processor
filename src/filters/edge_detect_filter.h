#pragma once
#include "filter_base.h"

class EdgeDetectFilter : public FilterBase {
public:
    EdgeDetectFilter()
        : low_threshold_(100.0)
        , high_threshold_(200.0) { }

    void apply(const cv::Mat& input, cv::Mat& output) override;
    bool isColor() const override { return false; }
    std::string getName() const override { return "edge_detect"; }
    void configure(const FilterConfig& config) override;

private:
    double low_threshold_;
    double high_threshold_;
};