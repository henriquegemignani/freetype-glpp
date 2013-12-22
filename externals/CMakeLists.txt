
option(FREETYPE-GLXX_INTERNAL_FREETYPE "Set to ON to use an internal freetype instead of the system one.." OFF)
option(FREETYPE-GLXX_INTERNAL_GLEW     "Set to ON to use an internal glew instead of the system one." OFF)

macro(check_package OPTION_VAR PKG_NAME)
    find_package(${PKG_NAME} ${ARGN} QUIET)
    if(NOT ${OPTION_VAR}_FOUND)
        message("-- ${PKG_NAME} not found, forcing internal.")
        set(FREETYPE-GLXX_INTERNAL_${OPTION_VAR} ON CACHE BOOL "Set to ON to use an internal ${PKG_NAME} instead of the system one." FORCE)
    endif()
endmacro(check_package)

check_package(FREETYPE Freetype)
check_package(GLEW GLEW 1.5)

if(FREETYPE-GLXX_INTERNAL_FREETYPE)
    add_subdirectory(externals/freetype)

else(FREETYPE-GLXX_INTERNAL_FREETYPE)
    add_library(freetype STATIC IMPORTED GLOBAL)
    set_target_properties(freetype PROPERTIES
        IMPORTED_LOCATION "${FREETYPE_LIBRARIES}"
        INTERFACE_INCLUDE_DIRECTORIES "${FREETYPE_INCLUDE_DIRS}")

endif(FREETYPE-GLXX_INTERNAL_FREETYPE)

if(NOT TARGET glew)
    if(FREETYPE-GLXX_INTERNAL_GLEW)
        add_subdirectory(externals/glew) # Defines 'glew'
    else(FREETYPE-GLXX_INTERNAL_GLEW)
        add_library(glew SHARED IMPORTED GLOBAL)
        set_target_properties(glew PROPERTIES
            IMPORTED_LOCATION "${GLEW_LIBRARIES}"
            INTERFACE_INCLUDE_DIRECTORIES "${GLEW_INCLUDE_DIRS}")
    endif(FREETYPE-GLXX_INTERNAL_GLEW)
endif(NOT TARGET glew)

add_subdirectory(freetype-gl)

