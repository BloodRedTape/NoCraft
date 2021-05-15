#include "platform/io.hpp"
#include "game_scene.hpp"
#include "main_menu_scene.hpp"
#include "render/ui_renderer.hpp"
#include "render/render_2d.hpp"
#include "world/generators/natural_world_generator.hpp"
#include "world/generators/extreme_world_generator.hpp"
#include "world/generators/super_flat_world_generator.hpp"

std::unique_ptr<WorldGenerator> GetGenerator(int index, u64 seed){
    switch (index) {
    case 0: return std::make_unique<NaturalWorldGenerator>(seed);
    case 1: return std::make_unique<ExtremeWorldGenerator>(seed);
    case 2: return std::make_unique<SuperFlatWorldGenerator>(seed);
    }
    Assert(false);
    return nullptr;
}

GameScene::GameScene(int world_type_index):
    m_World(std::move(GetGenerator(world_type_index, 534))),
    m_InventoryLayer(&m_Player)
{
    Chunk &spawn = m_World.Get({0,0});
    for(int i = 0; i<Chunk::SizeY; i++){
        if(spawn.Get({0,i,0}) == Block::Air){
            m_Player.SetPosition({0,i+1,0});
            break;
        }
    } 
}

void GameScene::OnUpdate(float dt){
    if(!m_CurrentLayer){
        m_Player.OnUpdate(dt);
    }else{
        m_CurrentLayer->OnUpdate(dt);
        if(!m_CurrentLayer)
            Mouse::SetGlobalPosition({m_Player.MouseResetPosition().x, m_Player.MouseResetPosition().y});
    }
    
    m_Player.RenderPlayerView();

    if(m_CurrentLayer)
        m_CurrentLayer->OnRender();
}

bool GameScene::OnEvent(const Event &e){
    if(m_CurrentLayer && m_CurrentLayer->OnEvent(e)){
        if(!m_CurrentLayer)
            Mouse::SetGlobalPosition({m_Player.MouseResetPosition().x, m_Player.MouseResetPosition().y});
        return true;
    }

    m_Player.OnEvent(e);

    if(e.Type == EventType::KeyPress){
        if(e.KeyPress.KeyCode == Key::Escape){
            PushLayer(&m_GamePauseLayer);
            return true;
        }
        if(e.KeyPress.KeyCode == Key::E){
            PushLayer(&m_InventoryLayer);
            return true;
        }
    }
    return false;
}