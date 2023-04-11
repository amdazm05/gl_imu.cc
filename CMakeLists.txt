cmake_minimum_required(VERSION 3.2)
project(gl_imu)
include_directories(
    ${PROJECT_SOURCE_DIR}/include/
)
add_library( ${PROJECT_NAME}
    STATIC
    ${PROJECT_SOURCE_DIR}/src/sensors/wt931.cc
)

add_executable(main
    ${PROJECT_SOURCE_DIR}/src/main.cc
)

target_link_libraries(
    main PUBLIC ${PROJECT_NAME}
)