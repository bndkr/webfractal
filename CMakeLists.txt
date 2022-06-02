cmake_minimum_required(VERSION 3.21)

project(Fractal)


# set(Boost_INCLUDE_DIR "C:/Program Files/boost/boost_1_79_0")
# set(Boost_NO_WARN_NEW_VERSIONS true)
# set(CMAKE_CXX_EXTENSIONS NEW)

set(boost_include_path "C:/Program Files/boost/boost_1_79_0" CACHE FILEPATH "The path to the Boost include directory")
set(boost_link_path "C:/Program Files/boost/boost_1_79_0/stage/lib" CACHE FILEPATH "The path to the build Boost libraries")
# find_package(Boost 1.40.0 REQUIRED COMPONENTS program_options)
include_directories(${boost_include_path})

set(src_list
main.cpp
Params.cpp
Params.hpp
Palette.cpp
Palette.hpp
)

link_directories(${boost_link_path})

add_executable(Fractal ${src_list})


