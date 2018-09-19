cmake_minimum_required(VERSION 3.0)

project(test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EIGEN3_ROOT      $ENV{EIGEN3_ROOT}      CACHE FILEPATH "Path to Eigen3"    )
set(BOOST_ROOT       $ENV{BOOST_ROOT}       CACHE FILEPATH "Path to Boost"     )
set(AMATRIX_ROOT     $ENV{AMATRIX_ROOT}     CACHE FILEPATH "Path to AMatrix"   )

include_directories(
    "${PROJECT_SOURCE_DIR}/include"
)

add_subdirectory(test)
