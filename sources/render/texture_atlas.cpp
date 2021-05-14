#include "texture_atlas.hpp"

TextureAtlas::TextureAtlas(const char *filepath, int element_width, int element_height):
    ElementWidth(element_width),
    ElementHeight(element_height)
{
    SamplerProperties props;
    props.MinFiltering = FilteringMode::Linear;
    props.MagFiltering = FilteringMode::Nearest;
    props.WrapU = WrapMode::ClampToEdge;
    props.WrapV = WrapMode::ClampToEdge;
    props.WrapS = WrapMode::ClampToEdge;

    auto res = MainTexture.LoadFromFile(filepath, props);
    Assert(res);
}

Pair<Vector2f, Vector2f> TextureAtlas::GetTextureCoordsBase(int block_index){
    auto size = MainTexture.GPUTexture.Size();
    int x_blocks = size.x / ElementWidth;
    int x = block_index%x_blocks;
    int y = block_index/x_blocks;
    return {Vector2f(float(x * ElementWidth)/size.x , float(y * ElementHeight)/size.y), {float(ElementWidth)/size.x, float(ElementHeight)/size.y}};
}


TextureAtlas &TextureAtlas::Get(){
    static TextureAtlas *atlas = new TextureAtlas("resources/texture_atlas.png");
    return *atlas;
}