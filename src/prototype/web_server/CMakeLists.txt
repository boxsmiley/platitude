cmake_minimum_required(VERSION 3.7)
project(web_server)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        HttpServer.cpp)


add_executable(web_server ${SOURCE_FILES})
target_link_libraries(web_server event pthread)