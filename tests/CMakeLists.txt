find_package(GTest REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENCV REQUIRED opencv4)

add_executable(test_video_processor 
    test_filter_factory.cpp
    ../src/filters/filter_factory.cpp
    ../src/filters/filter_processor.cpp
    ../src/filters/grayscale_filter.cpp
    ../src/filters/blur_filter.cpp
    ../src/filters/sharpen_filter.cpp
    ../src/filters/edge_detect_filter.cpp
)

target_include_directories(test_video_processor PRIVATE 
    ${GTEST_INCLUDE_DIRS}
    ${OPENCV_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    /usr/include/opencv4
)

target_link_libraries(test_video_processor 
    GTest::gtest_main
    ${OPENCV_LIBRARIES}
)

add_test(NAME test_video_processor COMMAND test_video_processor)