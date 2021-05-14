#ifndef GAME_PAUSE_LAYER_HPP
#define GAME_PAUSE_LAYER_HPP

#include "layers/base_ui_layer.hpp"
#include "ui/ui.hpp"

class GamePauseLayer: public BaseUILayer{
public:
    void OnUpdate(float dt)override;

    void OnRender()override;
    
    bool OnEvent(const Event &e)override;
};

#endif//GAME_PAUSE_LAYER_HPP