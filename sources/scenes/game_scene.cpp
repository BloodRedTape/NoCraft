#include "game_scene.hpp"
#include "platform/io.hpp"
#include "main_menu_scene.hpp"

GameScene::GameScene(){
    m_Player.Move({0, 40, 0});
}

void GameScene::OnUpdate(float dt){
    if(!m_CurrentLayer){
        m_Player.Update(dt);
    }else{
        m_CurrentLayer->OnUpdate(dt);
        if(!m_CurrentLayer)
            Mouse::SetGlobalPosition({m_Player.MouseResetPosition().x, m_Player.MouseResetPosition().y});
    }
    
    DisplayServer::Window.ClearColorBuffer(Color::LightBlue);
    DisplayServer::Window.ClearDepthBuffer();

    m_Renderer.Render(m_Player.GetCamera());

    m_UIRenderer.BeginScene(DisplayServer::Window.CurrentFramebuffer());
    {
        auto size = DisplayServer::Window.Size();
        Vector2i pointer_size(20, 5);
        m_UIRenderer.DrawRect({size.width/2 - pointer_size.x/2, size.height/2 - pointer_size.y/2}, {pointer_size.x, pointer_size.y}, Color(0,0,0,0.5f));
        m_UIRenderer.DrawRect({size.width/2 - pointer_size.y/2, size.height/2 - pointer_size.x/2}, {pointer_size.y, pointer_size.x}, Color(0,0,0,0.5f));
    }
    m_UIRenderer.EndScene();

    if(m_CurrentLayer)
        m_CurrentLayer->OnRender();

    DisplayServer::Window.SwapBuffers();
}

bool GameScene::OnEvent(const Event &e){
    if(m_CurrentLayer && m_CurrentLayer->OnEvent(e)){
        if(!m_CurrentLayer)
            Mouse::SetGlobalPosition({m_Player.MouseResetPosition().x, m_Player.MouseResetPosition().y});
        return true;
    }
    
    if(e.Type == EventType::MouseButtonPress){
        if(e.MouseButtonPress.Button == Mouse::Left){
            m_Player.Dig(m_World, m_Renderer);
            return true;
        }
        if(e.MouseButtonPress.Button == Mouse::Right){
            m_Player.Place(m_World, m_Renderer);
            return true;
        }
        if(e.MouseButtonPress.Button == Mouse::Middle){
            m_Player.Pick(m_World);
            return true;
        }
    }
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