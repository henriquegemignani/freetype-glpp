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
#include <freetype-gl++/texture-font.hpp>

#include <cassert>
#include "texture-font.h"

#include <freetype-gl++/texture-atlas.hpp>

namespace freetypeglxx {

float TextureGlyph::GetKerning(const wchar_t charcode) {
    return texture_glyph_get_kerning(static_cast<const texture_glyph_t *>(self_),
                                     charcode);
}

size_t TextureGlyph::width() const { return static_cast<const texture_glyph_t *>(self_)->width; }

size_t TextureGlyph::height() const { return static_cast<const texture_glyph_t *>(self_)->height; }

int TextureGlyph::offset_x() const { return static_cast<const texture_glyph_t *>(self_)->offset_x; }

int TextureGlyph::offset_y() const { return static_cast<const texture_glyph_t *>(self_)->offset_y; }

float TextureGlyph::advance_x() const { return static_cast<const texture_glyph_t *>(self_)->advance_x; }

float TextureGlyph::advance_y() const { return static_cast<const texture_glyph_t *>(self_)->advance_y; }

float TextureGlyph::s0() const { return static_cast<const texture_glyph_t *>(self_)->s0; }

float TextureGlyph::t0() const { return static_cast<const texture_glyph_t *>(self_)->t0; }

float TextureGlyph::s1() const { return static_cast<const texture_glyph_t *>(self_)->s1; }

float TextureGlyph::t1() const { return static_cast<const texture_glyph_t *>(self_)->t1; }

int TextureGlyph::outline_type() const { return static_cast<const texture_glyph_t *>(self_)->outline_type; }

TextureGlyph::TextureGlyph(void* data) : self_(data) {
    assert(self_);
}

//=====================================

TextureFont::TextureFont(TextureAtlas* atlas,
                         const std::string& filename,
                         const float size )
    : self_(texture_font_new_from_file(static_cast<texture_atlas_t*>(atlas->RawGet()),
                                       size,
                                       filename.c_str())),
      atlas_(atlas) {}

TextureFont::TextureFont(TextureAtlas* atlas,
                         const void *memory_base,
                         size_t memory_size,
                         const float size )
    : self_(texture_font_new_from_memory(static_cast<texture_atlas_t*>(atlas->RawGet()),
                                         size,
                                         memory_base,
                                         memory_size)),
      atlas_(atlas) {}

TextureFont::~TextureFont() {
    for(std::map<void*, TextureGlyph*>::iterator it = glyphs_.begin(); it != glyphs_.end(); ++it)
        delete it->second;
    texture_font_delete(static_cast<texture_font_t*>(self_));
}

TextureGlyph* TextureFont::GetGlyph(wchar_t charcode) {
    texture_glyph_t* glypht = texture_font_get_glyph(static_cast<texture_font_t*>(self_),
                                                    charcode);
    TextureGlyph*& glyphp = glyphs_[static_cast<void*>(glypht)];
    if(!glyphp)
        glyphp = new TextureGlyph(static_cast<void*>(glypht));
    return glyphp;
}

size_t TextureFont::LoadGlyphs(const wchar_t * charcodes) {
    return texture_font_load_glyphs(static_cast<texture_font_t*>(self_),
                                    charcodes);
}

float TextureFont::height() const { return static_cast<texture_font_t*>(self_)->height; }

TextureAtlas* TextureFont::atlas() const {
    assert(atlas_->RawGet() == static_cast<texture_font_t*>(self_)->atlas);
    return atlas_;
}

} // namespace freetypeglxx
