// TODO: license text
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
