cmake_minimum_required(VERSION 3.8)
project(space_invaders)

set(CMAKE_C_STANDARD 11)

set(CURSES_NEED_NCURSES true)
set(CMAKE_C_FLAGS "-Wall -pedantic")

find_package(Curses REQUIRED)
find_package(Threads REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

add_executable(main main.c main.h aliens.c aliens.h)
target_link_libraries(main ${CURSES_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})