#include "filter_factory.h"
#include "blur_filter.h"
#include "edge_detect_filter.h"
#include "grayscale_filter.h"
#include "sharpen_filter.h"

std::unordered_map<std::string, FilterFactory::FactoryFunction> FilterFactory::factories_;

void FilterFactory::initialize() {
    registerFilter<GrayscaleFilter>("grayscale");
    registerFilter<BlurFilter>("blur");
    registerFilter<SharpenFilter>("sharpen");
    registerFilter<EdgeDetectFilter>("edge_detect");
}