#pragma once
#include "filter_base.h"
#include "video_filter_service/config.h"
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

class FilterFactory {
public:
    using FactoryFunction = std::function<std::unique_ptr<FilterBase>(const FilterConfig&)>;

    template <typename T> static void registerFilter(const std::string& name) {
        factories_[name] = [](const FilterConfig& config) -> std::unique_ptr<FilterBase> {
            auto filter = std::make_unique<T>();
            filter->configure(config);
            return filter;
        };
    }

    static std::unique_ptr<FilterBase> createFilter(
        const std::string& name, const FilterConfig& config) {
        auto it = factories_.find(name);
        if (it != factories_.end()) {
            return it->second(config);
        }
        return nullptr;
    }

    static void initialize();

    static std::vector<std::string> getRegisteredFilters() {
        std::vector<std::string> names;
        for (const auto& pair : factories_) {
            names.push_back(pair.first);
        }
        return names;
    }

private:
    static std::unordered_map<std::string, FactoryFunction> factories_;
};