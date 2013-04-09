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
#ifndef FREETYPEGLXX_VERTEXBUFFER_H_
#define FREETYPEGLXX_VERTEXBUFFER_H_

#include <cstddef>
#include <string>
#include <vector>
#include <freetype-gl++/opengl.hpp>

namespace freetypeglxx {

/**
 * @file   vertex-buffer.hpp
 *
 * @defgroup vertex-buffer Vertex buffer
 *
 * @{
 */

class VertexBuffer {
  public:
    /**
     * Creates an empty vertex buffer.
     *
     * @param  format a string describing vertex format.
     * @return        an empty vertex buffer.
     */
    VertexBuffer(const std::string& format);

    /**
     * Deletes vertex buffer and releases GPU memory.
     *
     */
    ~VertexBuffer();

    /**
     *  Returns the number of items in the vertex buffer
     *
     *  @return       number of items
     */
    std::size_t size() const;

    /**
     *  Returns vertex format
     *
     *  @return       vertex format
     */
    const char* format() const;

    /**
     * Print information about a vertex buffer
     *
     */
    void Print();

    /**
     * Prepare vertex buffer for render.
     *
     * @param  mode  render mode
     */
    void RenderSetup(GLenum mode);

    /**
     * Finish rendering by setting back modified states
     *
     */
    void RenderFinish();

    /**
     * Render vertex buffer.
     *
     * @param  mode  render mode
     */
    void Render(GLenum mode);

    /**
     * Render a specified item from the vertex buffer.
     *
     * @param  index index of the item to be rendered 
     */
    void RenderItem(std::size_t index);

    /**
     * Upload buffer to GPU memory.
     *
     */
    void Upload();

    /**
     * Clear all items.
     *
     */
    void Clear();

    /**
     * Append a new item to the collection.
     *
     * @param  vcount   number of vertices
     * @param  vertices raw vertices data
     * @param  icount   number of indices
     * @param  indices  raw indices data
     */
    std::size_t PushBack(const void * vertices, std::size_t vcount,  
                         const GLuint * indices, std::size_t icount);

    /**
     * Append a new item to the collection.
     *
     * @param  vertices raw vertices data
     * @param  indices  raw indices data
     */
    template<class T>
    std::size_t PushBack(const std::vector<T>& vertices, 
                         const std::vector<GLuint>& indices) {
        return PushBack(static_cast<const void*>(vertices.data()), vertices.size(), 
                        indices.data(), indices.size());
    }

    /**
     * Insert a new item into the vertex buffer.
     *
     * @param  index     location before which to insert item
     * @param  vertices  raw vertices data
     * @param  vcount    number of vertices
     * @param  indices   raw indices data
     * @param  icount    number of indices
     */
    std::size_t Insert(std::size_t index,
                       const void * vertices, std::size_t vcount,  
                       const GLuint * indices, std::size_t icount);

    /**
     * Insert a new item into the vertex buffer.
     *
     * @param  index     location before which to insert item
     * @param  vertices  raw vertices data
     * @param  indices   raw indices data
     */
    template<class T>
    std::size_t Insert(std::size_t index,
                       const std::vector<T>& vertices,  
                       const std::vector<GLuint>& indices) {
        return Insert(index,
                      static_cast<const void*>(vertices.data()), vertices.size(),
                      indices.data(), indices.size());
    }

    /**
     * Erase an item from the vertex buffer.
     *
     * @param  index    index of the item to be deleted
     */
    void Erase(std::size_t index);

/** @} */
  private:
    void* self_;

};

} // namespace freetypeglxx

#endif // FREETYPEGLXX_VERTEXBUFFER_H_
