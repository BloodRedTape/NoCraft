#include "game_scene.hpp"

GameScene::GameScene(){
        
    Mouse::SetVisible(false);
    Mouse::SetGlobalPosition({800,400});
    m_Player.Move({0, 40, 0});
}

GameScene::~GameScene(){
    Mouse::SetVisible(true);
}

void GameScene::OnUpdate(float dt){

    m_Player.Update(dt);

    if(Keyboard::IsKeyPressed(Key::Q))
        Stop();

    DisplayServer::Window.ClearColorBuffer(Color::LightBlue);
    DisplayServer::Window.ClearDepthBuffer();

    m_Renderer.Render(m_Player.GetCamera());


    m_UIRenderer.BeginScene(DisplayServer::Window.CurrentFramebuffer());
    auto size = DisplayServer::Window.Size();
    Vector2i pointer_size(20, 5);
    m_UIRenderer.DrawRect({size.width/2 - pointer_size.x/2, size.height/2 - pointer_size.y/2}, {pointer_size.x, pointer_size.y}, Color(0,0,0,0.5f));
    m_UIRenderer.DrawRect({size.width/2 - pointer_size.y/2, size.height/2 - pointer_size.x/2}, {pointer_size.y, pointer_size.x}, Color(0,0,0,0.5f));

    m_UIRenderer.EndScene();

    DisplayServer::Window.SwapBuffers();
}

bool GameScene::OnEvent(const Event &e){
    if(e.Type == EventType::MouseButtonPress){
        if(e.MouseButtonPress.Button == Mouse::Left)
            m_Player.Dig(m_World, m_Renderer);
        if(e.MouseButtonPress.Button == Mouse::Right)
            m_Player.Place(m_World, m_Renderer);
        if(e.MouseButtonPress.Button == Mouse::Middle)
            m_Player.Pick(m_World);
    }
    return false;
}