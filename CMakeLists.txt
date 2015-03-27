CMAKE_MINIMUM_REQUIRED( VERSION 2.8.11 )

project(freetype-gl++ CXX C)

SET( CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules" ${CMAKE_MODULE_PATH} )
SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

option(FREETYPE-GLXX_BUILD_DEMOS "Build the library demos." ON)

add_subdirectory(externals)


SET( FREETYPE_GLXX_SRC include/freetype-gl++/freetype-gl++.hpp
                       include/freetype-gl++/vec234.hpp
                       include/freetype-gl++/texture-atlas.hpp src/texture-atlas.cpp
                       include/freetype-gl++/texture-font.hpp  src/texture-font.cpp
                       include/freetype-gl++/shader.hpp        src/shader.cpp
                       include/freetype-gl++/vertex-buffer.hpp src/vertex-buffer.cpp
                       src/dummy.cpp)

add_library( freetype-gl++ STATIC ${FREETYPE_GLXX_SRC} )

target_link_libraries( freetype-gl++ LINK_PUBLIC freetype-gl )
target_include_directories( freetype-gl++ PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
                       
if(FREETYPE-GLXX_BUILD_DEMOS)
    add_subdirectory(demos)
endif(FREETYPE-GLXX_BUILD_DEMOS)
