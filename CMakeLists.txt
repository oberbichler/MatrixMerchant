cmake_minimum_required(VERSION 3.0)

project(test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EIGEN3_ROOT      $ENV{EIGEN3_ROOT}      CACHE FILEPATH "Path to Eigen3"    )

include_directories(
    "${PROJECT_SOURCE_DIR}/include"
)

add_subdirectory(test)
