cmake_minimum_required(VERSION 3.2)
project(gl_imu)
cmake_policy(SET CMP0115 OLD)
set(CXX_STANDARD_REQUIRED 20)
set(CMAKE_CXX_FLAGS "-std=c++20 -fcoroutines")

option(EnableTests "Tests are Disabled" OFF)

include_directories(
    ${CMAKE_SOURCE_DIR}/libs/freeglut/include
    ${CMAKE_SOURCE_DIR}/libs/glfw/include
    ${CMAKE_SOURCE_DIR}/libs/glfw/deps
    ${CMAKE_SOURCE_DIR}/libs/glew-cmake/include
    )

add_subdirectory(${PROJECT_SOURCE_DIR}/libs/freeglut)
add_subdirectory(${PROJECT_SOURCE_DIR}/libs/glfw)
add_subdirectory(${PROJECT_SOURCE_DIR}/libs/glew-cmake)

if(EnableTests)
add_subdirectory(${PROJECT_SOURCE_DIR}/libs/googletest)
add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
endif(EnableTests)


include_directories(
    ${PROJECT_SOURCE_DIR}/include
)
add_library( ${PROJECT_NAME}
    STATIC
    # ${PROJECT_SOURCE_DIR}/src/sensors/wt931.cc
    ${PROJECT_SOURCE_DIR}/src/stream/serialstreamer
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC freeglut_static libglew_static glfw ${PROJECT_SOURCE_DIR}/thirdparty/build/libglad_core.a)
add_executable(main
    ${PROJECT_SOURCE_DIR}/app/app_main.cc
)

target_link_libraries(
    main PUBLIC 
    ${PROJECT_NAME} 
)