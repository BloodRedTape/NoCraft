#ifndef RENDER_2D_HPP
#define RENDER_2D_HPP

#include "graphics/texture.hpp"

using namespace StraitX;

class Render2D{
private:
    static Vector2f (&DefaultTextureCoords)[4];
public:
    static void Init();

    static void Begin();

    static void End();

    static void Flush();

    static void Clear(Color color = Color::Black, float depth = 1.0);

    static void SwapBuffers();

    static void DrawRect(Vector2i position, Vector2i size, const Color &color, const Texture &texture, Vector2f (&texture_coords)[4] = DefaultTextureCoords);

    static void DrawRect(Vector2i position, Vector2i size, const Color &color);

    static void DrawRect(Vector2i position, Vector2i size, const Texture &texture, Vector2f (&texture_coords)[4] = DefaultTextureCoords);

};

#endif//RENDER_2D_HPP