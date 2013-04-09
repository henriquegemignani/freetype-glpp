/* ============================================================================
 * Freetype GL++ - A C++ FreeType-GL wrapper
 * Platform:       Any
 * WWW:            https://github.com/henriquegemignani/freetype-glpp
 * ----------------------------------------------------------------------------
 * Copyright 2013 Henrique Gemignani. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY HENRIQUE GEMIGNANI ''AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL HENRIQUE GEMIGNANI OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of Henrique Gemignani.
 * ============================================================================
 * 
 *  This library is merely a wrapper of the Freetype GL by Nicolas P. Rougier.
 *  WWW: http://code.google.com/p/freetype-gl/
 * 
 * ============================================================================
 */
#include <freetype-gl++/vertex-buffer.hpp>

#include "vertex-buffer.h"

#define CASTED_SELF static_cast<vertex_buffer_t *>(self_)

namespace freetypeglxx {

VertexBuffer::VertexBuffer(const std::string& format)
    : self_(vertex_buffer_new(format.c_str())) {}

VertexBuffer::~VertexBuffer() {
    vertex_buffer_delete(CASTED_SELF);
}

std::size_t VertexBuffer::size() const {
    return vertex_buffer_size(CASTED_SELF);
}

const char* VertexBuffer::format() const {
    return vertex_buffer_format(CASTED_SELF);
}

void VertexBuffer::Print() {
    vertex_buffer_print(CASTED_SELF);
}

void VertexBuffer::RenderSetup(GLenum mode) {
    vertex_buffer_render_setup(CASTED_SELF, mode);
}

void VertexBuffer::RenderFinish() {
    vertex_buffer_render_finish(CASTED_SELF);
}

void VertexBuffer::Render(GLenum mode) {
    vertex_buffer_render(CASTED_SELF, mode);
}

void VertexBuffer::RenderItem(std::size_t index) {
    vertex_buffer_render_item(CASTED_SELF, index);
}

void VertexBuffer::Upload() {
    vertex_buffer_upload(CASTED_SELF);
}

void VertexBuffer::Clear() {
    vertex_buffer_clear(CASTED_SELF);
}

std::size_t VertexBuffer::PushBack(const void * vertices, std::size_t vcount,  
                                   const GLuint * indices, std::size_t icount) {
    return vertex_buffer_push_back(CASTED_SELF, vertices, vcount, indices, icount);
}

std::size_t VertexBuffer::Insert(std::size_t index,
                                 const void * vertices, std::size_t vcount,  
                                 const GLuint * indices, std::size_t icount) {
    return vertex_buffer_insert(CASTED_SELF, index, vertices, vcount, indices, icount);
}
                    
void VertexBuffer::Erase(std::size_t index) {
    vertex_buffer_erase(CASTED_SELF, index);
}

} // namespace freetypeglxx
