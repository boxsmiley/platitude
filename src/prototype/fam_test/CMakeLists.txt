cmake_minimum_required(VERSION 3.5.2)
project(fam_test)

execute_process(COMMAND sudo apt install libfam-dev fam)
execute_process(COMMAND sudo service fam start)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Fam.hh)
add_executable(fam_test ${SOURCE_FILES})
target_link_libraries(fam_test fam)
