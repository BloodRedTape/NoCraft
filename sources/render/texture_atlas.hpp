#ifndef TEXTURE_ATLAS_HPP
#define TEXTURE_ATLAS_HPP

#include "core/math/vector2.hpp"
#include "core/pair.hpp"
#include "graphics/texture.hpp"

using namespace StraitX;

struct TextureAtlas{
    static constexpr u32 BlockSize = 16;
    Texture MainTexture;

    TextureAtlas(const char *texture_path);

    Pair<Vector2f, float> GetTextureCoordsBase(int block_index);

    static TextureAtlas &Get();
};

#endif//TEXTURE_ATLAS_HPP