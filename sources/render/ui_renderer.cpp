#include "ui_renderer.hpp"
#include "utils/rect.hpp"
#include "servers/display_server.hpp"
#include <cmath>

UIRenderer::UIRenderer():
    Renderer2D(DisplayServer::Window.Pass()),
    m_Font("resources/font_2.png", s_GlyphWidth, s_GlyphHeight)
{
    SamplerProperties props;
    props.MagFiltering = FilteringMode::Nearest;

    auto res = m_ButtonTexture.LoadFromFile("resources/button.png", props);
    Assert(res);
}

void UIRenderer::HandleEvent(const Event &e){
    m_LastEvent = e;
}

void UIRenderer::Begin(){
    BeginScene(DisplayServer::Window.CurrentFramebuffer());
}

void UIRenderer::End(){
    EndScene();
    m_LastEvent.Type = EventType::Unknown;
}

void UIRenderer::DrawString(const std::string &string, int font_height, Vector2i position){
    int x_offset = 0;
    int font_width = std::ceil((float(s_GlyphWidth)/s_GlyphHeight) * font_height);
    for(char c: string){
        int index = CharToIndex(c);
        auto coords_data = m_Font.GetTextureCoordsBase(index);

        Vector2f coords[4] = {
            {coords_data.First.x,                        coords_data.First.y + coords_data.Second.y},
            {coords_data.First.x,                        coords_data.First.y},
            {coords_data.First.x + coords_data.Second.x, coords_data.First.y},
            {coords_data.First.x + coords_data.Second.x, coords_data.First.y + coords_data.Second.y},
        };

        DrawRect({position.x + x_offset, position.y}, {font_width, font_height}, m_Font.MainTexture, coords);

        x_offset += font_width;
    }
}

Vector2i UIRenderer::GetTextSize(const std::string &text, int font_height){
    int font_width = std::ceil((float(s_GlyphWidth)/s_GlyphHeight) * font_height);
    return {font_width * text.size(), font_height};
}

void UIRenderer::DrawButton(Vector2i position, Vector2i size, Color tint){
    DrawRect(position, size, tint, m_ButtonTexture);
}

bool UIRenderer::DoButton(const std::string &text, Vector2i position, Vector2i size){
    Rect button{position, position + size};
    DrawButton(button.Position(), button.Size(), button.Contains(MousePosition()) ? Color(0.8, 0.8, 0.8, 1.f) : Color::White);
    DrawString(text, 50, button.Position() + (button.Size()/2 - GetTextSize(text, 50)/2));
    return button.Contains(MousePosition()) && (m_LastEvent.Type == EventType::MouseButtonPress && m_LastEvent.MouseButtonPress.Button == Mouse::Left);
}

int UIRenderer::CharToIndex(char ch){
    if(ch >= 'A' && ch <= 'Z')
        return ch - 'A';
    if(ch >= 'a' && ch <= 'z')
        return 26 + (ch - 'a');
    if(ch >= '0' && ch <= '9')
        return 52 + (ch - '0');
    switch (ch) {
    case '.': return 62;
    case ',': return 63;
    case ';': return 64;
    case ':': return 65;
    case '$': return 66;
    case '#': return 67;
    case '\'': return 68;
    case '\"': return 69;
    case '\\': return 70;
    case '?': return 71;
    case '%': return 72;
    case '&': return 73;
    case '(': return 74;
    case ')': return 75;
    case '@': return 76;
    default: return 77;
    }
}

Vector2i UIRenderer::MousePosition(){
    auto pos = Mouse::RelativePosition(DisplayServer::Window);
    return {pos.x, DisplayServer::Window.Size().height - pos.y};
}