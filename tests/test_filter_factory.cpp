#include <gtest/gtest.h>
#include "filters/filter_factory.h"
#include "filters/filter_base.h"

TEST(FilterFactoryTest, CreateGrayscaleFilter) {
    FilterFactory::initialize();
    
    auto filter = FilterFactory::createFilter("grayscale", {});
    ASSERT_NE(filter, nullptr);
    EXPECT_EQ(filter->getName(), "grayscale");
}

TEST(FilterFactoryTest, CreateBlurFilterWithConfig) {
    FilterFactory::initialize();
    
    FilterConfig config;
    config.parameters["kernel_size"] = 21;
    config.parameters["sigma"] = 5.0;

    auto filter = FilterFactory::createFilter("blur", config);
    ASSERT_NE(filter, nullptr);
    EXPECT_EQ(filter->getName(), "blur");
}