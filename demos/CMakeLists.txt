CMAKE_MINIMUM_REQUIRED( VERSION 2.8.5 )

option(FREETYPE-GLXX_EMBEDDED_GLUT     "Use internal glut instead of system provided." ON)
                       
find_package( GLUT QUIET )
if(FREETYPE-GLXX_EMBEDDED_GLUT OR (NOT GLUT_FOUND))
	message("-- Using internal FreeGLUT.")
	set(FREETYPE-GLXX_EMBEDDED_GLUT ON)
    set(FREEGLUT_BUILD_SHARED_LIBS OFF CACHE BOOL "Build FreeGLUT shared library.")
    set(FREEGLUT_BUILD_STATIC_LIBS ON  CACHE BOOL "Build FreeGLUT static library.")
    set(FREEGLUT_BUILD_DEMOS       OFF  CACHE BOOL "Build FreeGLUT demos.")
	add_subdirectory(${CMAKE_SOURCE_DIR}/externals/freeglut freeglut)
    set(GLUT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/freeglut/include")
    set(GLUT_LIBRARIES    freeglut_static)
    add_definitions(-DFREEGLUT_STATIC)
endif()

include_directories( ${GLUT_INCLUDE_DIR} )

MACRO( DEMO _target _sources)
    add_executable(${_target} ${_sources})
    target_link_libraries(${_target} freetype-gl++)
    target_link_libraries(${_target} ${GLUT_LIBRARIES})
ENDMACRO( DEMO )

#DEMO( demo-texture          "demo-texture.c" )
DEMO( demo-font             "font/demo-font.cpp" )
#DEMO( demo-benchmark        "demo-benchmark.c" )
#DEMO( demo-console          "demo-console.c" )
#DEMO( demo-cube             "demo-cube.c" )
#DEMO( demo-glyph            "demo-glyph.c" )
#DEMO( demo-cartoon          "demo-cartoon.c" )
#DEMO( demo-outline          "demo-outline.c" )
#DEMO( demo-lcd              "demo-lcd.c" )
#DEMO( demo-gamma            "demo-gamma.c" )
#DEMO( demo-ansi             "demo-ansi.c" )
#DEMO( demo-subpixel         "demo-subpixel.c" )
#DEMO( demo-make             "demo-makefont.c;arial-16.h" )
#DEMO( makefont              "makefont.c" )
#DEMO( demo-distance-field   "demo-distance-field.c;edtaa3func.c")
#DEMO( demo-distance-field-2 "demo-distance-field-2.c;edtaa3func.c")
#DEMO( demo-distance-field-3 "demo-distance-field-3.c;edtaa3func.c")

# Copy font and shaders into build directory for in-place testing
#FILE(GLOB Fonts   "fonts/Vera.ttf"
#                  "fonts/VeraMoBI.ttf"
#                  "fonts/VeraMoBd.ttf"
#                  "fonts/VeraMoIt.ttf"
#                  "fonts/VeraMono.ttf"
#                  "fonts/ObelixPro.ttf")
#file(COPY ${Fonts}   DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/fonts)
#
#FILE(GLOB Data   "data/256colors.txt")
#file(COPY ${Data}   DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)
#
#FILE(GLOB Shaders "shaders/*.vert" "shaders/*.frag")
#file(COPY ${Shaders} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders)
