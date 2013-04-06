CMAKE_MINIMUM_REQUIRED( VERSION 2.8.5 )

project(freetype-gl++ CXX)

SET( FREETYPE_GLXX_SRC #src/freetype-gl++.hpp
                       src/dummy.cc)

add_library( freetype-gl++ STATIC ${FREETYPE_GLXX_SRC} )