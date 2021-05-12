#include "game_pause_layer.hpp"
#include "scenes/main_menu_scene.hpp"

void GamePauseLayer::OnUpdate(float dt){
    (void)dt;
}

void GamePauseLayer::OnRender(){
    UIRenderer.BeginScene(DisplayServer::Window.CurrentFramebuffer());
    {
        UIRenderer.DrawRect({0,0}, WindowSize, Color(0.2, 0.2, 0.2, 0.5f));
        UIRenderer.DrawRect(m_Exit.Position(), m_Exit.Size(), m_Exit.Contains(MousePosition()) ? Color(0.8, 0.8, 0.8, 1.f) : Color::White);

    }
    UIRenderer.EndScene();
}
    
bool GamePauseLayer::OnEvent(const Event &e){
    if(e.Type == EventType::MouseButtonPress){
        if(e.MouseButtonPress.Button == Mouse::Left){
            if(m_Exit.Contains(MousePosition())){
                SceneManager::SetScene(std::make_unique<MainMenuScene>());
                return true;
            }
        }
    }
    if(e.Type == EventType::KeyPress){
        if(e.KeyPress.KeyCode == Key::Escape){
            PopSelf();
            return true;
        }
    }
    return false;
}