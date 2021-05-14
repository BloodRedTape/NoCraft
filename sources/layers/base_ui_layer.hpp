#ifndef BASE_UI_LAYER_HPP
#define BASE_UI_LAYER_HPP

#include "utils/layers.hpp"
#include "utils/rect.hpp"

#include "render/ui_renderer.hpp"
#include "servers/display_server.hpp"

struct BaseUILayer: Layer{
    class UIRenderer UIRenderer;

    Vector2i WindowSize{DisplayServer::Window.Size().width, DisplayServer::Window.Size().height};

    Vector2i MousePosition(){
        auto pos = Mouse::RelativePosition(DisplayServer::Window);
        return {pos.x, DisplayServer::Window.Size().height - pos.y};
    }
};

#endif//BASE_UI_LAYER_HPP