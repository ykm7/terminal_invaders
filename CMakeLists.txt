cmake_minimum_required(VERSION 3.8)
project(space_invaders)

OPTION(build_test "Create the tests for this project." OFF)

add_subdirectory(src)
if(build_test)
    add_subdirectory(test)
endif(build_test)
