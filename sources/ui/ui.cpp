#include <vector>
#include "ui.hpp"
#include "render/ui_renderer.hpp"
#include "utils/rect.hpp"
#include "platform/mouse.hpp"
#include "servers/display_server.hpp"

static std::vector<Event> s_Events;

Vector2i MousePosition(){
    auto pos = Mouse::RelativePosition(DisplayServer::Window);
    return {pos.x, DisplayServer::Window.Size().height - pos.y};
}

void UI::UpdateUIState(const Event &e){
    s_Events.push_back(e);
}

void UI::ResetUIState(){
    s_Events.clear();
}

bool UI::EventMatch(std::function<bool(const Event &e)> matcher){
    for(auto &e: s_Events)
        if(matcher(e))
            return true;
    return false;
}

bool UI::Button(const std::string &text, Vector2i position, Vector2i size){
    Rect button{position, position + size};
    UIRenderer::DrawButton(button.Position(), button.Size(), button.Contains(MousePosition()) ? Color(0.8, 0.8, 0.8, 1.f) : Color::White);
    UI::Text(text, position, size);
    return button.Contains(MousePosition()) 
    && EventMatch([](const Event &e){
        return e.Type == EventType::MouseButtonPress && e.MouseButtonPress.Button == Mouse::Left;
    });
}

void UI::Text(const std::string &text, Vector2i position, Vector2i size){
    UIRenderer::DrawString(text, s_FontSize, position + (size/2 - UIRenderer::GetTextSize(text, s_FontSize)/2));
}

void UI::Selector(ArrayPtr<std::string> names, int &current_index, Vector2i position, Vector2i size){
    if(UI::Button(names[current_index], position, size))
        current_index = (current_index + 1)%names.Size();
}


VerticalLayout::VerticalLayout(Vector2i layout_origin, Vector2i layout_size, Vector2i button_size, s32 button_distance):
    m_LayoutOrigin(layout_origin),
    m_LayoutSize(layout_size),
    m_ButtonSize(button_size),
    m_ButtonDistance(button_distance),
    m_CurrentIndex(0)
{}

std::pair<Vector2i, Vector2i> VerticalLayout::NextPosAndSize(){
    std::pair<Vector2i, Vector2i> result{{m_LayoutOrigin.x + m_LayoutSize.x/2 - m_ButtonSize.x/2, m_LayoutOrigin.y - m_ButtonSize.y * m_CurrentIndex - m_ButtonDistance * m_CurrentIndex - m_ButtonSize.y}, m_ButtonSize};
    m_CurrentIndex++;
    return result;
}

bool VerticalLayout::Button(const std::string &text){
    auto pos_size = NextPosAndSize();
    auto press = UI::Button(text, pos_size.first, pos_size.second);
    return press;
}

void VerticalLayout::Selector(ArrayPtr<std::string> names, int &current_index){
    auto pos_size = NextPosAndSize();
    UI::Selector(names, current_index, pos_size.first, pos_size.second);
}

void VerticalLayout::Reset(){
    m_CurrentIndex = 0;
}

