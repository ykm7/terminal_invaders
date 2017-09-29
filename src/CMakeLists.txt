set(CMAKE_C_STANDARD 11)

set(CURSES_NEED_NCURSES true)
set(CMAKE_C_FLAGS "-Wall -pedantic")
set(EXECUTABLE_OUTPUT_PATH ${space_invaders_SOURCE_DIR}/build)

set(EXECUTABLE_NAME terminal_invaders)
list(APPEND SOURCE_FILES
        ${space_invaders_SOURCE_DIR}/src/bullets.c
        ${space_invaders_SOURCE_DIR}/src/ship.c
        ${space_invaders_SOURCE_DIR}/src/aliens.c
        ${space_invaders_SOURCE_DIR}/src/c_window.c
        ${space_invaders_SOURCE_DIR}/src/main.c
        )
set(HEADER_FILES ${space_invaders_SOURCE_DIR}/include)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})
target_link_libraries(${EXECUTABLE_NAME} ${CURSES_LIBRARIES})
