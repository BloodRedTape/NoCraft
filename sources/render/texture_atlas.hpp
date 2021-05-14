#ifndef TEXTURE_ATLAS_HPP
#define TEXTURE_ATLAS_HPP

#include "core/math/vector2.hpp"
#include "core/pair.hpp"
#include "graphics/texture.hpp"

using namespace StraitX;

struct TextureAtlas{
    Texture MainTexture;
    int ElementWidth;
    int ElementHeight;

    TextureAtlas(const char *texture_path, int element_width = 16, int element_height = 16);

    Pair<Vector2f, Vector2f> GetTextureCoordsBase(int block_index);

    static TextureAtlas &Get();
};

#endif//TEXTURE_ATLAS_HPP