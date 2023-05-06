cmake_minimum_required(VERSION 3.0)
project(glad_dep)
add_subdirectory(${PROJECT_SOURCE_DIR}/../libs/glad/cmake glad_cmake)
glad_add_library(glad_core STATIC LOCATION ${PROJECT_SOURCE_DIR}/../thirdparty/glad_core MX API gl:core=3.3)