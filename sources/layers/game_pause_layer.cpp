#include "game_pause_layer.hpp"
#include "scenes/main_menu_scene.hpp"
#include "render/render_2d.hpp"
#include "ui/ui.hpp"

void GamePauseLayer::OnUpdate(float dt){
    (void)dt;
}

void GamePauseLayer::OnRender(){
    Render2D::DrawRect({0,0}, WindowSize, Color(0.2, 0.2, 0.2, 0.5f));

    if(Button("Save and Quit"))
        SceneManager::SetScene(std::make_unique<MainMenuScene>());

    button_index = 0;
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

bool GamePauseLayer::Button(const std::string &text){
    auto pressed = UI::Button(text, {m_Exit.Position().x, m_Exit.Position().y + (m_Exit.Size().y * button_index) + button_padding*button_index}, m_Exit.Size());
    ++button_index;
    return pressed;
}