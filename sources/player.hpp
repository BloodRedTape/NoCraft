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
    Camera m_Camera{Camera::Perspective(100, -100, Rad(1), 1280.f/720)};
    float m_Speed = 60.f;
    float m_MouseSpeed = 1/6.f;
    float m_DigDistance = 6;
    float m_DigAccuracy = 0.01;

    Block m_Current = Block::OakWood;
public:
    void Update(float dt);

    const Camera &GetCamera()const{
        return m_Camera;
    }

    void Dig(World &world, WorldRenderer &renderer);

    void Place(World &world, WorldRenderer &renderer);

    void Pick(World &world);

    void Move(Vector3f g_direction);
};

#endif//PLAYER_HPP