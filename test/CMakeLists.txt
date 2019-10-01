cmake_minimum_required(VERSION 3.8)

add_executable(read_test read_test.cxx)
target_link_libraries(read_test stdc++fs)

add_executable(encode_test encode_test.cxx)
target_link_libraries(encode_test stdc++fs)

add_executable(write_test write_test.cxx)
target_link_libraries(write_test stdc++fs)