#ifndef UI_RENDERER_HPP
#define UI_RENDERER_HPP

#include <string>
#include "graphics/renderer_2d.hpp"
#include "texture_atlas.hpp"


using namespace StraitX;

class UIRenderer: public Renderer2D{
private:
    static constexpr int s_GlyphWidth = 6;
    static constexpr int s_GlyphHeight = 8;
    TextureAtlas m_Font;
    Texture m_ButtonTexture;
public:
    UIRenderer();

    void Begin();

    void End();

    void DrawString(const std::string &string, int font_height, Vector2i position);

    Vector2i GetTextSize(const std::string &text, int font_height);

    void DrawButton(Vector2i position, Vector2i size, Color tint);

    bool DoButton(const std::string &text, Vector2i position, Vector2i size);

private:
    int CharToIndex(char ch);

    Vector2i MousePosition();
};


#endif//UI_RENDERER_HPP