#ifndef BASE_UI_LAYER_HPP
#define BASE_UI_LAYER_HPP

#include "utils/layers.hpp"
#include "utils/rect.hpp"

#include "render/ui_renderer.hpp"
#include "servers/display_server.hpp"

struct BaseUILayer: Layer{

    Vector2i WindowSize{DisplayServer::Window.Size().width, DisplayServer::Window.Size().height};
};

#endif//BASE_UI_LAYER_HPP