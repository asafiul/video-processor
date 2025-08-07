find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENCV REQUIRED opencv4)

add_executable(video_filter_service
    main.cpp
    filters/filter_factory.cpp
    filters/filter_processor.cpp
    filters/grayscale_filter.cpp
    filters/blur_filter.cpp
    filters/sharpen_filter.cpp
    filters/edge_detect_filter.cpp
)

target_include_directories(video_filter_service PRIVATE 
    ${OPENCV_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    /usr/include/opencv4
)

target_link_libraries(video_filter_service 
    ${OPENCV_LIBRARIES}
)

set_target_properties(video_filter_service PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)