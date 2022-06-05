


add_subdirectory(fractals)

set(fractal_src ${fractal_src} PARENT_SCOPE)

set(src_list
src/Complex.hpp
src/FileOps.cpp
src/FileOps.hpp
src/Generator.cpp
src/Generator.hpp
src/main.cpp
src/Params.cpp
src/Params.hpp
src/Palette.cpp
src/Palette.hpp
${fractal_src} PARENT_SCOPE
)