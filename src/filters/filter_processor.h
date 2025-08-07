#pragma once
#include "filter_base.h"
#include "video_filter_service/config.h"
#include <memory>
#include <vector>

class FilterProcessor {
public:
    static std::vector<std::unique_ptr<FilterBase>> createFiltersFromConfig(
        const AppConfig& config);

    static void processVideo(const std::string& inputPath, const std::string& outputPath,
        const std::vector<std::unique_ptr<FilterBase>>& filters);
};