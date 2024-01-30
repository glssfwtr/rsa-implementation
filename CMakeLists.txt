cmake_minimum_required(VERSION 3.2)

project(rsa)

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -g -O0 -Wall -Wextra -Wcast-align -Wcast-qual -Wconversion -Wpedantic -Wpointer-arith -Wunused -Wunused-variable -fno-inline -Wshadow")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -march=native -Ofast -s -Wl,-s,--as-needed")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB project-sources

      "${CMAKE_SOURCE_DIR}/src/*.cpp"
      "${CMAKE_SOURCE_DIR}/src/*.hpp"

)

add_executable(qe
      ${project-sources}
)

add_custom_target(cleanbuild

      COMMAND ${CMAKE_MAKE_PROGRAM} clean
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR} # current CMakeFiles dir
      COMMENT "removing previous build artifacts..."

)

# build target right to left <====
add_dependencies(qe cleanbuild)
# add_dependencies(test_stage cleanbuild)