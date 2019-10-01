cmake_minimum_required(VERSION 3.8)
project(bin2cxx VERSION 0.1 LANGUAGES CXX)
add_executable(${PROJECT_NAME} main.cxx)
target_link_libraries(${PROJECT_NAME} stdc++fs)