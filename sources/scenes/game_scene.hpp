#ifndef GAME_HPP
#define GAME_HPP

#include "scene.hpp"
#include "world/world.hpp"
#include "render/world_renderer.hpp"
#include "player.hpp"

#include "layers/game_pause_layer.hpp"
#include "layers/inventory_layer.hpp"

class GameScene: public BaseScene{
private:
    World m_World;
    Player m_Player{&m_World};

    Layer *m_CurrentLayer = nullptr;

    GamePauseLayer m_GamePauseLayer;
    InventoryLayer m_InventoryLayer;

public:
    GameScene(int world_type_index);

    void OnUpdate(float dt)override;

    bool OnEvent(const Event &e)override;

    void PushLayer(Layer *layer){
        m_CurrentLayer = layer;
        m_CurrentLayer->Storage = &m_CurrentLayer;
    }

    void PopLayer(){
        if(m_CurrentLayer){
            m_CurrentLayer = nullptr;
        }
    }
};


#endif//GAME_HPP