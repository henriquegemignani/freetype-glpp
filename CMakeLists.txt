CMAKE_MINIMUM_REQUIRED( VERSION 2.8.5 )

project(freetype-gl++ CXX C)

SET( CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules" ${CMAKE_MODULE_PATH} )

option(FREETYPE-GLXX_EMBEDDED_FREETYPE "Use internal freetype instead of system provided." ON)
option(FREETYPE-GLXX_EMBEDDED_GLEW     "Use internal glew instead of system provided." ON)
option(FREETYPE-GLXX_BUILD_DEMOS       "Build the library demos." OFF)

find_package(Freetype QUIET)
if(FREETYPE-GLXX_EMBEDDED_FREETYPE OR (NOT FREETYPE_FOUND))
	message("-- Using internal freetype.")
	set(FREETYPE-GLXX_EMBEDDED_FREETYPE ON)
    add_definitions(-DFT2_BUILD_LIBRARY)
	add_subdirectory(externals/freetype)
    set(FREETYPE_INCLUDE_DIRS ${FREETYPE_INCLUDE_DIR})
    set(FREETYPE_LIBRARIES    ${FREETYPE_LIBRARY})
endif()
include_directories(${FREETYPE_INCLUDE_DIRS})

find_package(GLEW 1.5 QUIET)
if(FREETYPE-GLXX_EMBEDDED_GLEW OR (NOT GLEW_FOUND))
    message("-- Using internal GLEW.")
	set(FREETYPE-GLXX_EMBEDDED_GLEW ON)
    add_definitions(-DGLEW_STATIC)
	add_subdirectory(externals/glew)
	set(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})
	set(GLEW_LIBRARIES ${GLEW_LIBRARY})
endif()
include_directories(${GLEW_INCLUDE_DIRS})

add_subdirectory(externals/freetype-gl)
include_directories(externals/freetype-gl)
include_directories(include)

SET( FREETYPE_GLXX_SRC include/freetype-gl++/freetype-gl++.hpp
                       include/freetype-gl++/vec234.hpp
                       include/freetype-gl++/texture-atlas.hpp src/texture-atlas.cpp
                       include/freetype-gl++/texture-font.hpp  src/texture-font.cpp
                       include/freetype-gl++/shader.hpp        src/shader.cpp
                       src/dummy.cpp)

add_library( freetype-gl++ STATIC ${FREETYPE_GLXX_SRC} )

target_link_libraries( freetype-gl++ LINK_PUBLIC
                       freetype-gl )
                       
if(FREETYPE-GLXX_BUILD_DEMOS)
    add_subdirectory(demos)
endif(FREETYPE-GLXX_BUILD_DEMOS)
