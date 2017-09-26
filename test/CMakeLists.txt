set(CMAKE_C_STANDARD 11)

set(CURSES_NEED_NCURSES true)
set(CMAKE_C_FLAGS "-Wall -pedantic")
set(EXECUTABLE_OUTPUT_PATH ${space_invaders_SOURCE_DIR}/build)

set(EXECUTABLE_NAME unit_tests)
list(APPEND SOURCE_FILES
        ${space_invaders_SOURCE_DIR}/src/bullets.c
        ${space_invaders_SOURCE_DIR}/src/ship.c
        ${space_invaders_SOURCE_DIR}/src/aliens.c
        ${space_invaders_SOURCE_DIR}/src/c_window.c
        )
set(HEADER_FILES ${space_invaders_SOURCE_DIR}/include)
set(TEST_FILES test_main.cpp test_bullet.cpp test_alien.cpp)

find_package(Curses REQUIRED)
find_package(Threads REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES} ${TEST_FILES})
target_link_libraries(${EXECUTABLE_NAME} ${CURSES_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

