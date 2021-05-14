#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "scene.hpp"
#include "utils/rect.hpp"
#include "render/ui_renderer.hpp"

class MainMenuScene: public BaseScene{
private:
    UIRenderer m_UIRenderer;

    Vector2i m_WindowSize{DisplayServer::Window.Size().width, DisplayServer::Window.Size().height};

    Vector2i m_ButtonSize{m_WindowSize.x/2, m_WindowSize.y / 10};

    s32 m_OriginX = m_WindowSize.x/2 - m_ButtonSize.x/2;
    s32 m_OriginY = m_WindowSize.y/4;
    Rect m_Play{{m_OriginX, m_OriginY}, {m_OriginX + m_ButtonSize.x, m_OriginY + m_ButtonSize.y}};

    int button_index = 0;
    int button_padding = m_ButtonSize.y/4;

    Texture m_Background;
    Texture m_LoadingScreen;
public:
    MainMenuScene();

    void OnUpdate(float dt)override;

    bool OnEvent(const Event &e)override;

    bool MenuButton(const std::string &text);

    void OnPlayPressed();
};

#endif//MAIN_MENU_HPP