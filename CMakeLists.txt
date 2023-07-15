cmake_minimum_required(VERSION 3.0)
project(gl_imu)
if(UNIX)
execute_process(COMMAND bash setup.sh
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif(UNIX)

if(WIN32)
    execute_process(COMMAND setup.bat
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif(WIN32)

file(COPY ${PROJECT_SOURCE_DIR}/src/shaders/ DESTINATION ${CMAKE_BINARY_DIR}/shaders)

cmake_policy(SET CMP0115 OLD)
set(CXX_STANDARD_REQUIRED 20)
set(CMAKE_CXX_FLAGS "-std=c++20 -fcoroutines")

option(EnableTests "Tests are Disabled" ON)
option(GLFW_BUILD_EXAMPLES "Disabled examples from GLFW" OFF)
option(GLFW_BUILD_TESTS "Disabled GLFW Testss" OFF)
option(GLFW_BUILD_DOCS "Not building GLFW build docs" OFF)

include_directories(
    ${CMAKE_SOURCE_DIR}/libs/freeglut/include
    ${CMAKE_SOURCE_DIR}/libs/glfw/include
    ${CMAKE_SOURCE_DIR}/thirdparty/glad_core/include
    ${CMAKE_SOURCE_DIR}/libs/glfw/deps
    ${CMAKE_SOURCE_DIR}/libs/freetype/include
    ${CMAKE_SOURCE_DIR}/thirdparty/glad_core/include
    ${CMAKE_SOURCE_DIR}/libs
    )

add_subdirectory(${PROJECT_SOURCE_DIR}/libs/glfw)
add_subdirectory(${PROJECT_SOURCE_DIR}/libs/freetype)
add_subdirectory(${PROJECT_SOURCE_DIR}/libs/glm)

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
    ${PROJECT_SOURCE_DIR}/src/stream/serialstreamer.cc
    ${PROJECT_SOURCE_DIR}/src/graphics/window_component.cc
    ${PROJECT_SOURCE_DIR}/src/graphics/cursors_component.cc
    ${PROJECT_SOURCE_DIR}/src/graphics/text_component.cc
    ${PROJECT_SOURCE_DIR}/src/graphics/shader_handler.cc
    ${PROJECT_SOURCE_DIR}/src/graphics/geometric_shapes_component.cc
    ${PROJECT_SOURCE_DIR}/src/graphics/error_logger.cc
    ${PROJECT_SOURCE_DIR}/src/graphics/buffer/vertex_buffer.cc
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm glfw ${PROJECT_SOURCE_DIR}/thirdparty/build/libglad_core.a freetype)
add_executable(main
    ${PROJECT_SOURCE_DIR}/app/app_main.cc
)

target_link_libraries(
    main PUBLIC 
    ${PROJECT_NAME} 
)