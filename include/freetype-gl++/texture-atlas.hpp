// TODO: license text
#ifndef FREETYPEGLXX_TEXTUREATLAS_HPP_
#define FREETYPEGLXX_TEXTUREATLAS_HPP_

#include <freetype-gl++/vec234.hpp>

namespace freetypeglxx {

/** TODO, fix names?
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
                 const size_t depth);
      
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
    ivec4 GetRegion(const size_t width,
                    const size_t height);
    
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
                   const size_t stride );
    
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
