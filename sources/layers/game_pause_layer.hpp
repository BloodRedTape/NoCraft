#ifndef GAME_PAUSE_LAYER_HPP
#define GAME_PAUSE_LAYER_HPP

#include "layers/base_ui_layer.hpp"

class GamePauseLayer: public BaseUILayer{
private:

    Vector2i m_ButtonSize{WindowSize.x/2, WindowSize.y / 10};

    s32 m_OriginX = WindowSize.x/2 - m_ButtonSize.x/2;
    s32 m_OriginY = WindowSize.y/4;

    Rect m_Exit{{m_OriginX, m_OriginY}, {m_OriginX + m_ButtonSize.x, m_OriginY + m_ButtonSize.y}};
public:
    void OnUpdate(float dt)override;

    void OnRender()override;
    
    bool OnEvent(const Event &e)override;

};

#endif//GAME_PAUSE_LAYER_HPP