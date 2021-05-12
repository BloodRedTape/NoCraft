#ifndef MINECRAFT_HPP
#define MINECRAFT_HPP

#include "main/application.hpp"
#include "world/world.hpp"
#include "render/world_renderer.hpp"
#include "player.hpp"
#include "world/generators/extreme_world_generator.hpp"
#include "world/generators/natural_world_generator.hpp"

#include "graphics/renderer_2d.hpp"
#include "servers/display_server.hpp"

using namespace StraitX;

class Minecraft: public Application{
private:
    World m_World{std::move(std::make_unique<NaturalWorldGenerator>(12345))};
    WorldRenderer m_Renderer{&m_World};
    Player m_Player;

    Renderer2D m_UIRenderer{DisplayServer::Window.Pass()};
public:
    Result OnInitialize()override;

    void OnUpdate(float dt)override;

    bool OnEvent(const Event &e)override;

    void OnFinalize()override;
};

#endif//MINECRAFT_HPP