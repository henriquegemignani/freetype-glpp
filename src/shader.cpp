// TODO: license text
#include <freetype-gl++/shader.hpp>

#include "shader.h"

namespace freetypeglxx {
namespace glutility {


char * Read( const char *filename ) {
    return shader_read(filename);
}

GLuint Compile( const char* source,
                const GLenum type ) {
    return shader_compile(source, type);
}

GLuint Load( const char * vert_filename,
             const char * frag_filename ) {
    return shader_load(vert_filename, frag_filename);
}

GLuint Get( GLuint self,
            const char * name ) {
    return shader_get(self, name);
}

/** @} */

} // namespace glutility
} // namespace freetypeglxx
