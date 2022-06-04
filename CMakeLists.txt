cmake_minimum_required(VERSION 3.21)

project(Fractal)

set(boost_include_path "C:/Program Files/boost/boost_1_79_0" CACHE FILEPATH "The path to the Boost include directory")
set(boost_link_path "C:/Program Files/boost/boost_1_79_0/stage/lib" CACHE FILEPATH "The path to the build Boost libraries")

add_subdirectory(src)

include_directories(${boost_include_path})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
link_directories(${boost_link_path})

source_group(fractals FILES ${fractal_src})

add_executable(Fractal ${src_list})


