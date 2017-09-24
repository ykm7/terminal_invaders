set(CMAKE_C_STANDARD 11)

set(CURSES_NEED_NCURSES true)
set(CMAKE_C_FLAGS "-Wall -pedantic")
set(EXECUTABLE_OUTPUT_PATH ${space_invaders_SOURCE_DIR}/build)

find_package(Curses REQUIRED)
find_package(Threads REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})
include_directories(${space_invaders_SOURCE_DIR}/inc)

add_executable(terminal_invaders main.c aliens.c c_window.c ../include/c_window.h bullets.c ../include/bullets.h)
target_link_libraries(terminal_invaders ${CURSES_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
