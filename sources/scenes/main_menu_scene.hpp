#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "scene.hpp"
#include "utils/rect.hpp"
#include "graphics/renderer_2d.hpp"
#include "servers/display_server.hpp"

class MainMenuScene: public BaseScene{
private:
    Renderer2D m_UIRenderer{DisplayServer::Window.Pass()};

    Vector2i m_WindowSize{DisplayServer::Window.Size().width, DisplayServer::Window.Size().height};

    Vector2i m_ButtonSize{m_WindowSize.x/2, m_WindowSize.y / 10};

    s32 m_OriginX = m_WindowSize.x/2 - m_ButtonSize.x/2;
    s32 m_OriginY = m_WindowSize.y/4;
    Rect m_Play{{m_OriginX, m_OriginY}, {m_OriginX + m_ButtonSize.x, m_OriginY + m_ButtonSize.y}};

public:
    MainMenuScene();

    void OnUpdate(float dt)override;

    bool OnEvent(const Event &e)override;

    Vector2i MousePosition(){
        auto pos = Mouse::RelativePosition(DisplayServer::Window);
        return {pos.x, DisplayServer::Window.Size().height - pos.y};
    }

    void OnPlayPressed();
};

#endif//MAIN_MENU_HPP