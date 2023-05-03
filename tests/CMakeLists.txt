cmake_minimum_required(VERSION 3.1)
set(TEST_NAME BUFFERTEST)
set(TEST_SOURCE buffertest.cc)
add_executable(${TEST_NAME} ${TEST_SOURCE})
target_link_libraries(${TEST_NAME} 
     PUBLIC 
        gtest_main
        gl_imu
)
add_test(
    NAME ${TEST_NAME}
    COMMAND ${TEST_NAME}
)