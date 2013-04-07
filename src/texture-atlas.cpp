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
#include <freetype-gl++/texture-atlas.hpp>
#include <cstring>

#include "texture-atlas.h"

namespace freetypeglxx {

TextureAtlas::TextureAtlas(const size_t width, 
                           const size_t height,
                           const size_t depth)
      :  self_(texture_atlas_new(width, height, depth)) {}
      

TextureAtlas::~TextureAtlas() { 
    texture_atlas_delete(static_cast<texture_atlas_t*>(self_));
}

void TextureAtlas::Upload() { 
    texture_atlas_upload(static_cast<texture_atlas_t*>(self_));
}

ivec4 TextureAtlas::GetRegion(const size_t width,
                              const size_t height) {
    ivec4 return_value;
    memcpy(return_value.data,
           texture_atlas_get_region(static_cast<texture_atlas_t*>(self_), width, height).data,
           sizeof(return_value.data));
    return return_value;
}

void TextureAtlas::SetRegion(const size_t x,
                             const size_t y,
                             const size_t width,
                             const size_t height,
                             const unsigned char *data,
                             const size_t stride ) {
    texture_atlas_set_region(static_cast<texture_atlas_t*>(self_), x, y, width, height, data, stride);
}

void TextureAtlas::Clear() {
    texture_atlas_clear(static_cast<texture_atlas_t*>(self_));
}

unsigned int TextureAtlas::id() const { return static_cast<texture_atlas_t*>(self_)->id; }

} // namespace freetypeglxx
