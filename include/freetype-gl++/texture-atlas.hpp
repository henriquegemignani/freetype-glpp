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
#ifndef FREETYPEGLXX_TEXTUREATLAS_HPP_
#define FREETYPEGLXX_TEXTUREATLAS_HPP_

#include <cstddef>
#include <freetype-gl++/vec234.hpp>

namespace freetypeglxx {

/**
 * @file   texture-atlas.hpp
 *
 * @defgroup texture-atlas Texture atlas
 *
 * A texture atlas is used to pack several small regions into a single texture.
 *
 * The actual implementation is based on the article by Jukka Jylänki : "A
 * Thousand Ways to Pack the Bin - A Practical Approach to Two-Dimensional
 * Rectangle Bin Packing", February 27, 2010.
 * More precisely, this is an implementation of the Skyline Bottom-Left
 * algorithm based on C++ sources provided by Jukka Jylänki at:
 * http://clb.demon.fi/files/RectangleBinPack/
 *
 *
 * Example Usage:
 * @code
 * #include <freetype-gl++/texture-atlas.hpp>
 *
 * ...
 *
 * / Creates a new atlas of 512x512 with a depth of 1
 * freetypeglxx::TextureAtlas *atlas = new freetypeglxx::TextureAtlas(512, 512, 1);
 *
 * // Allocates a region of 20x20
 * freetypeglxx::ivec4 region = atlas->GetRegion(20, 20);
 *
 * // Fill region with some data
 * atlas->SetRegion(region.x, region.y, region.width, region.height, data, stride)
 *
 * ...
 *
 * @endcode
 *
 * @{
 */

class TextureAtlas {
  public:
    /**
     * Creates a new empty texture atlas.
     *
     * @param   width   width of the atlas
     * @param   height  height of the atlas
     * @param   depth   bit depth of the atlas
     *
     */
    TextureAtlas(const std::size_t width, 
                 const std::size_t height,
                 const std::size_t depth);
      
    /**
     *  Deletes a texture atlas.
     *
     */
    ~TextureAtlas();
    
    /**
     *  Upload atlas to video memory.
     *
     */
    void Upload();
    
    /**
     *  Allocate a new region in the atlas.
     *
     *  @param width  width of the region to allocate
     *  @param height height of the region to allocate
     *  @return       Coordinates of the allocated region
     *
     */
    ivec4 GetRegion(const std::size_t width,
                    const std::size_t height);
    
    /**
     *  Upload data to the specified atlas region.
     *
     *  @param x      x coordinate the region
     *  @param y      y coordinate the region
     *  @param width  width of the region
     *  @param height height of the region
     *  @param data   data to be uploaded into the specified region
     *  @param stride stride of the data
     *
     */
    void SetRegion(const std::size_t x,
                   const std::size_t y,
                   const std::size_t width,
                   const std::size_t height,
                   const unsigned char *data,
                   const std::size_t stride );
    
    /**
     *  Remove all allocated regions from the atlas.
     *
     *  @param self   a texture atlas structure
     */
    void Clear();
    
    /**
     * Texture identity (OpenGL)
     */
    unsigned int id() const;
    
    /**
     *  Returns the implementation pointer.
     *  For internal library use (or advanced uses).
     *
     * @return A texture_atlas_t pointer as a void*. You must cast it yourself.
     */
    void* RawGet() { return self_; }
    
  private:
    void* self_;
};

/** @} */

} // namespace freetypeglxx

#endif // FREETYPEGLXX_TEXTUREATLAS_HPP_
