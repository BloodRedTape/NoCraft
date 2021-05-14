#ifndef UI_RENDERER_HPP
#define UI_RENDERER_HPP

#include <string>
#include "texture_atlas.hpp"
#include "platform/events.hpp"

using namespace StraitX;

class UIRenderer{
private:
    static constexpr int s_GlyphWidth = 6;
    static constexpr int s_GlyphHeight = 8;
public:
    static void Init();

    static void SetNewUIState(const Event &e);

    static void Begin();

    static void End();

    static void DrawString(const std::string &string, int font_height, Vector2i position);

    static Vector2i GetTextSize(const std::string &text, int font_height);

    static void DrawButton(Vector2i position, Vector2i size, Color tint);

    static bool DoButton(const std::string &text, Vector2i position, Vector2i size);

private:
    static int CharToIndex(char ch);

    static Vector2i MousePosition();
};


#endif//UI_RENDERER_HPP