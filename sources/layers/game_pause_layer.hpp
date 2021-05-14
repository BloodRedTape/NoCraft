#ifndef GAME_PAUSE_LAYER_HPP
#define GAME_PAUSE_LAYER_HPP

#include "layers/base_ui_layer.hpp"

class GamePauseLayer: public BaseUILayer{
private:

    Vector2i m_ButtonSize{WindowSize.x/2, WindowSize.y / 10};

    s32 m_OriginX = WindowSize.x/2 - m_ButtonSize.x/2;
    s32 m_OriginY = WindowSize.y/2 - m_ButtonSize.y/2;

    Rect m_Exit{{m_OriginX, m_OriginY}, {m_OriginX + m_ButtonSize.x, m_OriginY + m_ButtonSize.y}};

    int button_index = 0;
    int button_padding = m_ButtonSize.y/4;
public:
    void OnUpdate(float dt)override;

    void OnRender()override;
    
    bool OnEvent(const Event &e)override;

    bool Button(const std::string &text);
};

#endif//GAME_PAUSE_LAYER_HPP