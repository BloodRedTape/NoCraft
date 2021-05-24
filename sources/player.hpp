#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "render/camera.hpp"
#include "utils/math.hpp"
#include "core/math/vector2.hpp"
#include "core/pair.hpp"
#include "world/world.hpp"
#include "render/world_renderer.hpp"

class Player{
private:
    World *m_World;
    WorldRenderer m_Renderer;

    Vector2i m_WindowSize;

    Camera m_Camera{Camera::Perspective(100, -100, Rad(1), 1280.f/720)};
    float m_Speed = 60.f;
    float m_MouseSpeed = 1/6.f;
    float m_DigDistance = 6;
    float m_DigAccuracy = 0.01;
private:
    static constexpr int s_InventorySize = 9;
    int m_Current = 0;
    Block m_InventoryBar[s_InventorySize]{Block::Dirt, Block::Grass, Block::OakWood, Block::BirchLeaves, Block::Sand, Block::Water};

    float m_SlotSize = m_WindowSize.x / 20.f;
    float m_BarSize = s_InventorySize * m_SlotSize;
    Texture m_BarSlot;
    Texture m_BarSelector;
private:
    Vector3f m_Movement;
public:
    Player(World *world);

    void OnUpdate(float dt);

    void OnEvent(const Event &e);

    void RenderPlayerView();

    void Select(Block block);
private:
    void RenderCursor();

    void RenderBar();

    void RenderDebugInfo();

    void Dig();

    void Place();

    void Pick();

    void Move(Vector3f g_direction);

public:
    void SetPosition(Vector3f position);
    
    Vector2i MouseResetPosition(){
        return {800, 400};
    }

};

#endif//PLAYER_HPP