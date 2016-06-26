cmake_minimum_required(VERSION 3.3)
project(isbh)

include_directories(
        src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES
        src/Oligo.cpp
        src/GraphCreator.cpp
        src/GraphElements.cpp
        src/DnaAssembler.cpp
        src/utils.cpp)

add_executable(isbh ${SOURCE_FILES} src/main.cpp)

add_executable(Tests ${SOURCE_FILES} tests/main_tests.cpp tests/tests.cpp)