#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "scene.hpp"
#include "utils/rect.hpp"
#include "graphics/texture.hpp"
#include "ui/ui.hpp"

class MainMenuScene: public BaseScene{
private:
    Vector2i m_WindowSize{DisplayServer::Window.Size().width, DisplayServer::Window.Size().height};

    Texture m_Background;
    Texture m_Logo;
    Texture m_LoadingScreen;
public:
    MainMenuScene();

    void OnUpdate(float dt)override;

    void OnPlayPressed();
};

#endif//MAIN_MENU_HPP