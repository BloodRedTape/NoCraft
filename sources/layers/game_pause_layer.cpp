#include "game_pause_layer.hpp"
#include "scenes/main_menu_scene.hpp"
#include "render/render_2d.hpp"
#include "ui/ui.hpp"

void GamePauseLayer::OnUpdate(float dt){
    (void)dt;
}

void GamePauseLayer::OnRender(){
    Render2D::DrawRect({0,0}, WindowSize, Color(0.2, 0.2, 0.2, 0.5f));

    VerticalLayout layout{{0, WindowSize.y/2}, {WindowSize.x, WindowSize.y/2}, {WindowSize.x/2, WindowSize.y / 10}, WindowSize.y / 40};

    if(layout.Button("Save and Quit"))
        SceneManager::SetScene(std::make_unique<MainMenuScene>());
}
    
bool GamePauseLayer::OnEvent(const Event &e){    
    if(e.Type == EventType::KeyPress){
        if(e.KeyPress.KeyCode == Key::Escape){
            PopSelf();
            return true;
        }
    }
    return false;
}
