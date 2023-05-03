cmake_minimum_required(VERSION 3.2)
project(gl_imu)
cmake_policy(SET CMP0115 OLD)
set(CXX_STANDARD_REQUIRED 20)
set(CMAKE_CXX_FLAGS "-std=c++20 -fcoroutines")

option(EnableTests "Tests are Disabled" OFF)

include_directories(
    ${PROJECT_SOURCE_DIR}/include/
)
add_library( ${PROJECT_NAME}
    STATIC
    # ${PROJECT_SOURCE_DIR}/src/sensors/wt931.cc
    ${PROJECT_SOURCE_DIR}/src/stream/serialstreamer
)

add_executable(main
    ${PROJECT_SOURCE_DIR}/app/app_main.cc
)

target_link_libraries(
    main PUBLIC ${PROJECT_NAME}
)