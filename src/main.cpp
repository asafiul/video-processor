#include "filters/filter_factory.h"
#include "filters/filter_processor.h"
#include "video_filter_service/config.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main() {
    try {
        FilterFactory::initialize();

        AppConfig config = AppConfig::loadFromFile("../config/app_config.json");

        if (!fs::exists(config.input_dir)) {
            fs::create_directories(config.input_dir);
        }
        if (!fs::exists(config.output_dir)) {
            fs::create_directories(config.output_dir);
        }

        std::string inputPath = config.input_dir + "/input.mp4";
        std::string outputPath = config.output_dir + "/output_processed.mp4";

        if (!fs::exists(inputPath)) {
            std::cerr << "Input video not found: " << inputPath << std::endl;
            std::cerr << "Please place your video file in: " << inputPath << std::endl;
            return 1;
        }

        auto filters = FilterProcessor::createFiltersFromConfig(config);

        if (filters.empty()) {
            std::cout << "No filters enabled, copying original video..." << std::endl;
        }

        FilterProcessor::processVideo(inputPath, outputPath, filters);
        std::cout << "Video processed and saved to: " << outputPath << std::endl;

        // Загрузка в облако (пример)
        // std::string filename = "output_processed.mp4";
        // std::string s3Url = "s3://" + config.s3_bucket + "/" + filename;
        // std::cout << "Uploaded to: " << s3Url << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}