cmake_minimum_required(VERSION 3.8)
project(bin2cxx VERSION 0.1 LANGUAGES CXX)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(${PROJECT_NAME} main.cxx)
target_link_libraries(${PROJECT_NAME} stdc++fs)

enable_testing()
if (BUILD_TESTING)
    add_subdirectory(test)

    add_test(read test/read_test ${CMAKE_CURRENT_SOURCE_DIR}/test/qr.png)
    set_tests_properties(read PROPERTIES
            PASS_REGULAR_EXPRESSION "pass"
            FAIL_REGULAR_EXPRESSION "failed")

    add_test(encode test/encode_test ${CMAKE_CURRENT_SOURCE_DIR}/test/qr.hxx)
    set_tests_properties(encode PROPERTIES
            PASS_REGULAR_EXPRESSION "pass"
            FAIL_REGULAR_EXPRESSION "failed")

    add_test(write test/write_test)
    set_tests_properties(encode PROPERTIES
            PASS_REGULAR_EXPRESSION "pass")
endif ()