// TODO: license text
#include <freetype-gl++/texture-font.hpp>

#include <cassert>
#include "texture-font.h"

#include <freetype-gl++/texture-atlas.hpp>

namespace freetypeglxx {

float TextureGlyph::GetKerning(const wchar_t charcode) {
    return texture_glyph_get_kerning(static_cast<const texture_glyph_t *>(self_),
                                     charcode);
}

TextureGlyph::TextureGlyph(void* data) : self_(data) {
    assert(self_);
}

//=====================================

TextureFont::TextureFont(TextureAtlas* atlas,
                         const char* filename,
                         const float size )
    : self_(texture_font_new(static_cast<texture_atlas_t*>(atlas->RawGet()),
                             filename,
                             size)) {}
                             
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

} // namespace freetypeglxx
