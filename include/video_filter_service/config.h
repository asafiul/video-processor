#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct FilterConfig {
    bool enabled = true;
    std::unordered_map<std::string, json> parameters;
};

struct AppConfig {
    std::string s3_bucket;
    std::string temp_dir;
    std::string input_dir;
    std::string output_dir;
    std::vector<std::string> processing_pipeline;
    std::unordered_map<std::string, FilterConfig> filter_configs;

    static AppConfig loadFromFile(const std::string& path);
};

inline AppConfig AppConfig::loadFromFile(const std::string& path) {
    std::ifstream f(path);
    if (!f.is_open()) {
        throw std::runtime_error("Cannot open config file: " + path);
    }
    
    json data = json::parse(f);
    
    AppConfig config;
    config.s3_bucket = data.value("s3_bucket", "default-bucket");
    config.temp_dir = data.value("temp_dir", "./temp");
    config.input_dir = data.value("input_dir", "../data/input");
    config.output_dir = data.value("output_dir", "../data/output");
    
    if (data.contains("processing_pipeline")) {
        for (const auto& filter : data["processing_pipeline"]) {
            config.processing_pipeline.push_back(filter);
        }
    }
    
    if (data.contains("filters")) {
        for (auto& [filterName, filterConfig] : data["filters"].items()) {
            FilterConfig cfg;
            cfg.enabled = filterConfig.value("enabled", true);
            
            for (auto& [paramName, paramValue] : filterConfig.items()) {
                cfg.parameters[paramName] = paramValue;
            }
            
            config.filter_configs[filterName] = cfg;
        }
    }
    
    return config;
}