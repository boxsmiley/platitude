cmake_minimum_required(VERSION 3.7)
project(common)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        DataStore.hh
        main.cpp)

add_executable(server ${SOURCE_FILES})
target_link_libraries(server zmq)

add_executable(client client.cpp)
target_link_libraries(client zmq)

