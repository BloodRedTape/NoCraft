#ifndef GAME_HPP
#define GAME_HPP

#include "scene.hpp"
#include "world/world.hpp"
#include "render/world_renderer.hpp"
#include "player.hpp"
#include "world/generators/extreme_world_generator.hpp"
#include "world/generators/natural_world_generator.hpp"

#include "graphics/renderer_2d.hpp"
#include "servers/display_server.hpp"

class GameScene: public BaseScene{
private:
    World m_World{std::move(std::make_unique<NaturalWorldGenerator>(12345))};
    WorldRenderer m_Renderer{&m_World};
    Player m_Player;

    Renderer2D m_UIRenderer{DisplayServer::Window.Pass()};
public:
    GameScene();

    ~GameScene();

    void OnUpdate(float dt)override;

    bool OnEvent(const Event &e)override;
};


#endif//GAME_HPP