#ifndef GAME_PAUSE_LAYER_HPP
#define GAME_PAUSE_LAYER_HPP

#include "utils/layers.hpp"
#include "ui/ui.hpp"
#include "servers/display_server.hpp"

class GamePauseLayer: public Layer{
    Vector2i WindowSize{DisplayServer::Window.Size().width, DisplayServer::Window.Size().height};
public:
    void OnUpdate(float dt)override;

    void OnRender()override;
    
    bool OnEvent(const Event &e)override;
};

#endif//GAME_PAUSE_LAYER_HPP