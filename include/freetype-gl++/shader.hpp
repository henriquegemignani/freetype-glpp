// TODO: license text
#ifndef FREETYPEGLXX_SHADER_H_
#define FREETYPEGLXX_SHADER_H_

#include <freetype-gl++/opengl.hpp>

namespace freetypeglxx {
namespace shader {

/**
 * @file   shader.h
 * @author Nicolas Rougier (Nicolas.Rougier@inria.fr)
 *
 * @defgroup shader Shader
 *
 * Simple functions for loading/building a shader from sources.
 *
 * <b>Example Usage</b>:
 * @code
 * #include "shader.h"
 *
 * int main( int arrgc, char *argv[] )
 * {
 *     GLuint shader = shader_load("shader.vert", "shader.frag");
 *
 *     return 0;
 * }
 * @endcode
 *
 * @{
 */

/**
 * Read a fragment or vertex shader from a file
 *
 * @param filename file to read shader from
 * @return         a newly-allocated text buffer containing code. This buffer
 *                 must be freed after usage.
 *
 */
  char * Read( const char *filename );


/**
 * Compile a shader from a text buffer.
 *
 * @param source code of the shader
 * @param type   type of the shader
 *
 * @return a handle on the compiled program
 *
 */
  GLuint Compile( const char* source,
                  const GLenum type );


/**
 * Load a vertex and fragment shader sources and build program
 *
 * @param  vert_filename vertex shader filename
 * @param  frag_filename fragment shader filename
 *
 * @return a handle on the built program
 *
 */
  GLuint Load( const char * vert_filename,
               const char * frag_filename );


/**
 *
 */
  GLuint Get( GLuint self,
              const char * name );

/** @} */

} // namespace shader
} // namespace freetypeglxx

#endif // FREETYPEGLXX_SHADER_H_
