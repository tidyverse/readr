cmake_minimum_required(VERSION 3.6)
project(readr)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(R_LIBRARY "~/R-library")
set(R_INCLUDE "/usr/share/R/include")

include_directories(${R_LIBRARY}/BH/include)
include_directories(${R_LIBRARY}/Rcpp/include)
include_directories(${R_INCLUDE})
include_directories(inst/include)
include_directories(src)

add_definitions(-D__CLION__)

file(GLOB SOURCE_FILES src/*.cpp src/*.c)
add_library(readr ${SOURCE_FILES})

add_custom_target(
    Rinstall
    # Using MAKEFLAGS=-j$(nproc) didn't work
    COMMAND MAKEFLAGS=-j8 nice R CMD INSTALL --libs-only --no-test-load ${readr_SOURCE_DIR}
)
