cmake_minimum_required(VERSION 3.1)
set(BufferTests BUFFERTEST)
set(BufferTests_SOURCE buffertest.cc)
add_executable(${BufferTests} ${BufferTests_SOURCE})
add_executable(CONVTESTS spaceconversiontests.cc)

target_link_libraries(${BufferTests} 
     PUBLIC 
        gtest_main
        gl_imu
)

target_link_libraries(CONVTESTS
     PUBLIC 
        gtest_main
        gl_imu
)

add_test(
    NAME ${BufferTests}
    COMMAND ${BufferTests}
)

add_test(
    NAME CONVTESTS
    COMMAND CONVTESTS
)