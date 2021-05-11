#include "texture_atlas.hpp"

TextureAtlas::TextureAtlas(const char *filepath){
    SamplerProperties props;
    props.MinFiltering = FilteringMode::Linear;
    props.MagFiltering = FilteringMode::Nearest;
    props.WrapU = WrapMode::ClampToEdge;
    props.WrapV = WrapMode::ClampToEdge;
    props.WrapS = WrapMode::ClampToEdge;

    auto res = MainTexture.LoadFromFile(filepath, props);
    Assert(res);
}

Pair<Vector2f, float> TextureAtlas::GetTextureCoordsBase(int block_index){
    auto size = MainTexture.GPUTexture.Size();
    int x_blocks = size.x / BlockSize;
    int x = block_index%x_blocks;
    int y = block_index/x_blocks;
    return {Vector2f(float(x * BlockSize)/size.x , float(y * BlockSize)/size.y), {float(BlockSize)/size.x}};
}


TextureAtlas &TextureAtlas::Get(){
    static TextureAtlas *atlas = new TextureAtlas("resources/texture_atlas.png");
    return *atlas;
}