/* ============================================================================
 * Freetype GL - A C OpenGL Freetype engine
 * Platform:    Any
 * WWW:         http://code.google.com/p/freetype-gl/
 * ----------------------------------------------------------------------------
 * Copyright 2011,2012 Nicolas P. Rougier. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY NICOLAS P. ROUGIER ''AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL NICOLAS P. ROUGIER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of Nicolas P. Rougier.
 * ============================================================================
 *
 * Example showing regular font usage
 *
 * ============================================================================
 */

#include <cstdio>
#include <cwchar>

#include "mat4.h"
#include <freetype-gl++/freetype-gl++.hpp>
#include <freetype-gl++/shader.hpp>
#include <freetype-gl++/vertex-buffer.hpp>
#if defined(__APPLE__)
    #include <Glut/glut.h>
#else
    #include <GL/glut.h>
#endif

using freetypeglxx::vec2;
using freetypeglxx::vec4;
using freetypeglxx::TextureFont;
using freetypeglxx::TextureGlyph;
using freetypeglxx::TextureAtlas;
using freetypeglxx::VertexBuffer;


// ------------------------------------------------------- typedef & struct ---
struct vertex_t {
    vertex_t(double _x, double _y, double _z, 
             double _s, double _t, 
             double _r, double _g, double _b, double _a)
             : x(_x), y(_y), z(_z), s(_s), t(_t), r(_r), g(_g), b(_b), a(_a) {}

    float x, y, z;    // position
    float s, t;       // texture
    float r, g, b, a; // color
};


// ------------------------------------------------------- global variables ---
GLuint shader;
VertexBuffer *buffer;
mat4   model, view, projection;


// ---------------------------------------------------------------- display ---
void display( void )
{
    glClearColor( 1, 1, 1, 1 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glUseProgram( shader );
    {
        glUniform1i( glGetUniformLocation( shader, "texture" ),
                     0 );
        glUniformMatrix4fv( glGetUniformLocation( shader, "model" ),
                            1, 0, model.data);
        glUniformMatrix4fv( glGetUniformLocation( shader, "view" ),
                            1, 0, view.data);
        glUniformMatrix4fv( glGetUniformLocation( shader, "projection" ),
                            1, 0, projection.data);
        buffer->Render( GL_TRIANGLES );
    }
    glutSwapBuffers( );
}


// ---------------------------------------------------------------- reshape ---
void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    mat4_set_orthographic( &projection, 0, width, 0, height, -1, 1);
}


// --------------------------------------------------------------- keyboard ---
void keyboard( unsigned char key, int x, int y )
{
    if ( key == 27 )
    {
        exit( 1 );
    }
}


// --------------------------------------------------------------- add_text ---
void add_text( VertexBuffer *buffer, TextureFont* font,
               const wchar_t * text, vec4 * color, vec2 * pen )
{
    size_t i;
    float r = color->red, g = color->green, b = color->blue, a = color->alpha;
    GLuint indices_raw[6] = {0,1,2, 0,2,3};
    std::vector<GLuint> indices(6);
    memcpy(indices.data(), indices_raw, sizeof(indices_raw));
    for( i=0; i<wcslen(text); ++i )
    {
        TextureGlyph* glyph = font->GetGlyph(text[i]);
        if( glyph != NULL )
        {
            int kerning = 0;
            if( i > 0)
            {
                kerning = glyph->GetKerning( text[i-1] );
            }
            pen->x += kerning;
            int x0  = (int)( pen->x + glyph->offset_x() );
            int y0  = (int)( pen->y + glyph->offset_y() );
            int x1  = (int)( x0 + glyph->width() );
            int y1  = (int)( y0 - glyph->height() );
            std::vector<vertex_t> vertices;
            vertices.push_back(vertex_t(x0,y0,0,  glyph->s0(),glyph->t0(),  r,g,b,a ));
            vertices.push_back(vertex_t(x0,y1,0,  glyph->s0(),glyph->t1(),  r,g,b,a ));
            vertices.push_back(vertex_t(x1,y1,0,  glyph->s1(),glyph->t1(),  r,g,b,a ));
            vertices.push_back(vertex_t(x1,y0,0,  glyph->s1(),glyph->t0(),  r,g,b,a ));
            buffer->PushBack(vertices, indices);
            pen->x += glyph->advance_x();
        }
    }
}


// ------------------------------------------------------------------- main ---
int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitWindowSize( 800, 400 );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutCreateWindow( argv[0] );
    glutReshapeFunc( reshape );
    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf( stderr, "Error: %s\n", glewGetErrorString(err) );
        exit( EXIT_FAILURE );
    }
    fprintf( stderr, "Using GLEW %s\n", glewGetString(GLEW_VERSION) );

    TextureAtlas *atlas = new TextureAtlas( 512, 512, 1 );
    const char * filename = "fonts/Vera.ttf";
    const wchar_t *text = L"A Quick Brown Fox Jumps Over The Lazy Dog 0123456789";
    buffer = new VertexBuffer( "vertex:3f,tex_coord:2f,color:4f" );
    vec2 pen = {{5,400}};
    vec4 black = {{0,0,0,1}};
    for(size_t i = 7; i < 27; ++i) {
        TextureFont *font = new TextureFont( atlas, filename, i );
        pen.x = 5;
        pen.y -= font->height();
        font->LoadGlyphs( text );
        add_text( buffer, font, text, &black, &pen );
        delete font;
    }
    glBindTexture( GL_TEXTURE_2D, atlas->id() );

    shader = freetypeglxx::shader::Load("shaders/v3f-t2f-c4f.vert",
                                        "shaders/v3f-t2f-c4f.frag");
    mat4_set_identity( &projection );
    mat4_set_identity( &model );
    mat4_set_identity( &view );

    glutMainLoop( );
    return 0;
}
