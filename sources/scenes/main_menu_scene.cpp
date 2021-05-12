#include "platform/io.hpp"
#include "main_menu_scene.hpp"
#include "game_scene.hpp"

MainMenuScene::MainMenuScene(){
    Println("WindowSize: %", m_WindowSize);
    Println("ButtonSize: %", m_ButtonSize);
    Println("Origin: %", m_OriginX);

    Println("% %", m_Play.Begin, m_Play.End);
}

void MainMenuScene::OnUpdate(float dt){
    DisplayServer::Window.ClearColorBuffer(Color(0.2, 0.2, 0.2, 1.0f));

    m_UIRenderer.BeginScene(DisplayServer::Window.CurrentFramebuffer());
    m_UIRenderer.DrawRect(m_Play.Position(), m_Play.Size(), m_Play.Contains(MousePosition()) ? Color(0.8, 0.8, 0.8, 1.f) : Color::White);
    m_UIRenderer.EndScene();

    DisplayServer::Window.SwapBuffers();
}

bool MainMenuScene::OnEvent(const Event &e){
    if(e.Type == EventType::MouseButtonPress){
        if(e.MouseButtonPress.Button == Mouse::Left){
            if(m_Play.Contains(MousePosition()))
                OnPlayPressed();
        }
    }
    return false;
}

void MainMenuScene::OnPlayPressed(){
    DisplayServer::Window.ClearColorBuffer();

    DisplayServer::Window.SwapBuffers();

    SceneManager::SetScene(std::make_unique<GameScene>());

}