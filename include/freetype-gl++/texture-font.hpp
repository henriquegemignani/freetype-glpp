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
#ifndef FREETYPEGLXX_TEXTUREFONT_HPP_
#define FREETYPEGLXX_TEXTUREFONT_HPP_

#include <map>
#include <string>
#include <freetype-gl++/texture-atlas.hpp>

namespace freetypeglxx {

/**
 * @file   texture-font.hpp
 *
 * @defgroup texture-font Texture font
 *
 * Texture font.
 *
 * Example Usage:
 * @code
 * #include <freetype-gl++/texture-font.hpp>
 *
 * int main( int arrgc, char *argv[] )
 * {
 *   return 0;
 * }
 * @endcode
 *
 * @{
 */

/*
 * Glyph metrics:
 * --------------
 *
 *                       xmin                     xmax
 *                        |                         |
 *                        |<-------- width -------->|
 *                        |                         |    
 *              |         +-------------------------+----------------- ymax
 *              |         |    ggggggggg   ggggg    |     ^        ^
 *              |         |   g:::::::::ggg::::g    |     |        | 
 *              |         |  g:::::::::::::::::g    |     |        | 
 *              |         | g::::::ggggg::::::gg    |     |        | 
 *              |         | g:::::g     g:::::g     |     |        | 
 *    offset_x -|-------->| g:::::g     g:::::g     |  offset_y    | 
 *              |         | g:::::g     g:::::g     |     |        | 
 *              |         | g::::::g    g:::::g     |     |        | 
 *              |         | g:::::::ggggg:::::g     |     |        |  
 *              |         |  g::::::::::::::::g     |     |      height
 *              |         |   gg::::::::::::::g     |     |        | 
 *  baseline ---*---------|---- gggggggg::::::g-----*--------      |
 *            / |         |             g:::::g     |              | 
 *     origin   |         | gggggg      g:::::g     |              | 
 *              |         | g:::::gg   gg:::::g     |              | 
 *              |         |  g::::::ggg:::::::g     |              | 
 *              |         |   gg:::::::::::::g      |              | 
 *              |         |     ggg::::::ggg        |              | 
 *              |         |         gggggg          |              v
 *              |         +-------------------------+----------------- ymin
 *              |                                   |
 *              |------------- advance_x ---------->|
 */

class TextureGlyph {
  public:
    /**
     * Get the kerning between two horizontal glyphs.
     *
     * @param charcode  codepoint of the peceding glyph
     * 
     * @return x kerning value
     */
    float GetKerning(const wchar_t charcode);
    
    /// Glyph's width in pixels.
    size_t width() const;

    /// Glyph's height in pixels.
    size_t height() const;

    /// Glyph's left bearing expressed in integer pixels.
    int offset_x() const;

    /**
     * Glyphs's top bearing expressed in integer pixels.
     *
     * Remember that this is the distance from the baseline to the top-most
     * glyph scanline, upwards y coordinates being positive.
     */
    int offset_y() const;

    /**
     * For horizontal text layouts, this is the horizontal distance (in
     * fractional pixels) used to increment the pen position when the glyph is
     * drawn as part of a string of text.
     */
    float advance_x() const;

    /**
     * For vertical text layouts, this is the vertical distance (in fractional
     * pixels) used to increment the pen position when the glyph is drawn as
     * part of a string of text.
     */
    float advance_y() const;

    /// First normalized texture coordinate (x) of top-left corner
    float s0() const;

    /// Second normalized texture coordinate (y) of top-left corner
    float t0() const;

    /// First normalized texture coordinate (x) of bottom-right corner
    float s1() const;

    /// Second normalized texture coordinate (y) of bottom-right corner
    float t1() const;

    /// Glyph outline type (0 = None, 1 = line, 2 = inner, 3 = outer)
    int outline_type() const;

  private:
    TextureGlyph(void* data);
  
    void* self_;
    
    friend class TextureFont;
};

class TextureAtlas;
class TextureFont {
  public:
    /**
     * This function creates a new texture font from given filename and size.  The
     * texture atlas is used to store glyph on demand. Note the depth of the atlas
     * will determine if the font is rendered as alpha channel only (depth = 1) or
     * RGB (depth = 3) that correspond to subpixel rendering (if available on your
     * freetype implementation).
     *
     * @param atlas     A texture atlas
     * @param filename  A font filename
     * @param size      Size of font to be created (in points)
     *
     * @return A new empty font (no glyph inside yet)
     *
     */
    TextureFont(TextureAtlas* atlas,
                const std::string& filename,
                const float size );

    /**
     * Delete a texture font. Note that this does not delete the glyph from the
     * texture atlas.
     *
     */
    ~TextureFont();

    /**
     * Request a new glyph from the font. If it has not been created yet, it will
     * be. 
     *
     * @param charcode Character codepoint to be loaded.
     *
     * @return A pointer to TextureGlyph or NULL if the texture atlas is not big
     *         enough. The Glyph is deleted when this TextureFont is deleted.
     *
     */
    TextureGlyph* GetGlyph(wchar_t charcode);


    /**
     * Request the loading of several glyphs at once.
     *
     * @param self      a valid texture font
     * @param charcodes character codepoints to be loaded.
     *
     * @return Number of missed glyph if the texture is not big enough to hold
     *         every glyphs.
     */
    size_t LoadGlyphs(const wchar_t * charcodes);
    
    /// Getters
    /**
     * This field is simply used to compute a default line spacing (i.e., the
     * baseline-to-baseline distance) when writing text with this font. Note
     * that it usually is larger than the sum of the ascender and descender
     * taken as absolute values. There is also no guarantee that no glyphs
     * extend above or below subsequent baselines when using this distance.
     */
    float height() const;
    
    //TODO
    TextureAtlas* atlas() const;
    
  private:
    void* self_;
    std::map<void*, TextureGlyph*> glyphs_;
    TextureAtlas* atlas_;
};

/** @} */

} // namespace freetypeglxx

#endif // FREETYPEGLXX_TEXTUREFONT_HPP_