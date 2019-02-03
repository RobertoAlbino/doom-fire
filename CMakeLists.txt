cmake_minimum_required(VERSION 3.10)

project(DoomFire)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

include_directories(include)

file(GLOB SOURCES "src/*.cpp" "*.c")

add_executable(DoomFire ${SOURCES})
target_link_libraries(DoomFire ${CURSES_LIBRARY})
