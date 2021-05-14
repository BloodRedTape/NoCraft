#include "ui.hpp"
#include "render/ui_renderer.hpp"
#include "utils/rect.hpp"
#include "platform/mouse.hpp"
#include "servers/display_server.hpp"

static Event s_LastEvent{EventType::Unknown};

Vector2i MousePosition(){
    auto pos = Mouse::RelativePosition(DisplayServer::Window);
    return {pos.x, DisplayServer::Window.Size().height - pos.y};
}

void UI::SetUIState(const Event &e){
    s_LastEvent = e;
}

void UI::ResetUIState(){
    s_LastEvent.Type = EventType::Unknown;
}

bool UI::Button(const std::string &text, Vector2i position, Vector2i size){
    Rect button{position, position + size};
    UIRenderer::DrawButton(button.Position(), button.Size(), button.Contains(MousePosition()) ? Color(0.8, 0.8, 0.8, 1.f) : Color::White);
    UIRenderer::DrawString(text, 50, button.Position() + (button.Size()/2 - UIRenderer::GetTextSize(text, 50)/2));
    return button.Contains(MousePosition()) && (s_LastEvent.Type == EventType::MouseButtonPress && s_LastEvent.MouseButtonPress.Button == Mouse::Left);
}


VerticalLayout::VerticalLayout(Vector2i layout_origin, Vector2i layout_size, Vector2i button_size, s32 button_distance):
    m_LayoutOrigin(layout_origin),
    m_LayoutSize(layout_size),
    m_ButtonSize(button_size),
    m_ButtonDistance(button_distance),
    m_CurrentIndex(0)
{}

bool VerticalLayout::Button(const std::string &text){
    auto press = UI::Button(text, {m_LayoutOrigin.x + m_LayoutSize.x/2 - m_ButtonSize.x/2, m_LayoutOrigin.y + m_ButtonSize.y * m_CurrentIndex + m_ButtonDistance * m_CurrentIndex}, m_ButtonSize);
    m_CurrentIndex++;
    return press;
}

void VerticalLayout::Reset(){
    m_CurrentIndex = 0;
}

