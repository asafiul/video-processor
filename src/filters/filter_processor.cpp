#include "filter_processor.h"
#include "filter_factory.h"
#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

std::vector<std::unique_ptr<FilterBase>> FilterProcessor::createFiltersFromConfig(
    const AppConfig& config) {

    std::vector<std::unique_ptr<FilterBase>> filters;

    for (const auto& filterName : config.processing_pipeline) {
        auto configIt = config.filter_configs.find(filterName);
        FilterConfig filterConfig;

        if (configIt != config.filter_configs.end()) {
            filterConfig = configIt->second;
        }

        if (filterConfig.enabled) {
            auto filter = FilterFactory::createFilter(filterName, filterConfig);
            if (filter) {
                filters.push_back(std::move(filter));
                std::cout << "Added filter: " << filterName << std::endl;
            } else {
                std::cerr << "Warning: Unknown filter '" << filterName << "'" << std::endl;
            }
        }
    }

    return filters;
}

void FilterProcessor::processVideo(const std::string& inputPath, const std::string& outputPath,
    const std::vector<std::unique_ptr<FilterBase>>& filters) {

    cv::VideoCapture cap(inputPath);
    if (!cap.isOpened()) {
        throw std::runtime_error("Cannot open video file: " + inputPath);
    }

    cv::VideoWriter writer;
    cv::Mat frame;

    std::vector<FilterBase*> filterPointers;
    for (const auto& filter : filters) {
        filterPointers.push_back(filter.get());
    }

    while (cap.read(frame)) {
        cv::Mat processedFrame = frame.clone();

        for (auto* filter : filterPointers) {
            cv::Mat tempFrame;
            filter->apply(processedFrame, tempFrame);
            processedFrame = tempFrame;
        }

        if (!writer.isOpened()) [[unlikely]]{
            int fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
            double fps = cap.get(cv::CAP_PROP_FPS);
            cv::Size size(processedFrame.cols, processedFrame.rows);

            bool isColorOutput = filterPointers.empty() ? true : filterPointers.back()->isColor();
            writer.open(outputPath, fourcc, fps, size, isColorOutput);
        }

        writer.write(processedFrame);
    }

    cap.release();
    writer.release();
}