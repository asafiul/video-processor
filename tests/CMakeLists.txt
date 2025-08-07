find_package(GTest REQUIRED)

add_executable(test_video_processor 
    test_video_processor.cpp
    ../src/video_processor.cpp
    ../src/filters/grayscale_filter.cpp
)

target_include_directories(test_video_processor PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(test_video_processor 
    GTest::gtest_main
    ${OpenCV_LIBS}
)

add_test(NAME test_video_processor COMMAND test_video_processor)
