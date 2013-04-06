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
 * This source is based on the article by Jukka Jylänki :
 * "A Thousand Ways to Pack the Bin - A Practical Approach to
 * Two-Dimensional Rectangle Bin Packing", February 27, 2010.
 *
 * More precisely, this is an implementation of the Skyline Bottom-Left
 * algorithm based on C++ sources provided by Jukka Jylänki at:
 * http://clb.demon.fi/files/RectangleBinPack/
 *
 *  ============================================================================
 */
#ifndef FREETYPEGLXX_TEXTURE_ATLAS_H_
#define FREETYPEGLXX_TEXTURE_ATLAS_H_

#include "texture-atlas.h"
#include <cstring>

namespace freetypeglxx {

/**
 * @file   texture-atlas.h
 * @author Nicolas Rougier (Nicolas.Rougier@inria.fr)
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
 * #include "texture-atlas.h"
 *
 * ...
 *
 * / Creates a new atlas of 512x512 with a depth of 1
 * texture_atlas_t * atlas = texture_atlas_new( 512, 512, 1 );
 *
 * // Allocates a region of 20x20
 * ivec4 region = texture_atlas_get_region( atlas, 20, 20 );
 *
 * // Fill region with some data
 * texture_atlas_set_region( atlas, region.x, region.y, region.width, region.height, data, stride )
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
    TextureAtlas(const size_t width, 
                 const size_t height,
                 const size_t depth)
      :  self_(texture_atlas_new(width, height, depth)) {}
      
    /**
     *  Deletes a texture atlas.
     *
     */
    ~TextureAtlas() { texture_atlas_delete(self_); }
    
    /**
     *  Upload atlas to video memory.
     *
     */
    void Upload() { texture_atlas_upload(self_); }
    
    /**
     *  Allocate a new region in the atlas.
     *
     *  @param width  width of the region to allocate
     *  @param height height of the region to allocate
     *  @return       Coordinates of the allocated region
     *
     */
    ivec4 GetRegion(const size_t width,
                    const size_t height) {
        ivec4 return_value;
        memcpy(return_value.data,
               texture_atlas_get_region(self_, width, height).data,
               sizeof(return_value.data));
        return return_value;
    }
    
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
    void SetRegion(const size_t x,
                   const size_t y,
                   const size_t width,
                   const size_t height,
                   const unsigned char *data,
                   const size_t stride ) {
        texture_atlas_set_region(self_, x, y, width, height, data, stride);
    }
    
    /**
     *  Remove all allocated regions from the atlas.
     *
     *  @param self   a texture atlas structure
     */
    void Clear() {
        texture_atlas_clear(self_);
    }
    
  private:
    texture_atlas_t* self_;
};

/** @} */

} // namespace freetypeglxx

#endif // FREETYPEGLXX_TEXTURE_ATLAS_H_
