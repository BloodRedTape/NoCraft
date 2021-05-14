#include "platform/io.hpp"
#include "main_menu_scene.hpp"
#include "game_scene.hpp"

MainMenuScene::MainMenuScene(){
    Println("WindowSize: %", m_WindowSize);
    Println("ButtonSize: %", m_ButtonSize);
    Println("Origin: %", m_OriginX);

    Println("% %", m_Play.Begin, m_Play.End);
    SamplerProperties props;
    props.MagFiltering = FilteringMode::Nearest;

    m_Background.LoadFromFile("resources/background.png");
    m_Logo.LoadFromFile("resources/logo.png");
    m_LoadingScreen.LoadFromFile("resources/dirt.png", props);
}

void MainMenuScene::OnUpdate(float dt){
    DisplayServer::Window.ClearColorBuffer(Color(0.2, 0.2, 0.2, 1.0f));

    m_UIRenderer.Begin();
    {
        m_UIRenderer.DrawRect({0,0}, m_WindowSize, m_Background);
        m_UIRenderer.DrawRect({m_WindowSize.x/4, m_WindowSize.y/2}, {m_WindowSize.x/2, m_WindowSize.y/4}, m_Logo);

        if(MenuButton("Exit")){
            Stop();
        }

        if(MenuButton("Play")){
            OnPlayPressed();
            return;
        }
    }
    m_UIRenderer.End();
    button_index = 0;

    DisplayServer::Window.SwapBuffers();
}

bool MainMenuScene::OnEvent(const Event &e){
    m_UIRenderer.HandleEvent(e);
    return false;
}

bool MainMenuScene::MenuButton(const std::string &text){
    auto pressed = m_UIRenderer.DoButton(text, {m_Play.Position().x, m_Play.Position().y + (m_Play.Size().y * button_index) + button_padding*button_index}, m_Play.Size());
    ++button_index;
    return pressed;
}

void MainMenuScene::OnPlayPressed(){
    DisplayServer::Window.ClearColorBuffer();
    m_UIRenderer.Begin();
    {
        float step_size = float(m_WindowSize.y)/15;

        for(int i = 0; i<m_WindowSize.y/step_size; i++){
            for(int j = 0; j<m_WindowSize.x/step_size; j++){
                m_UIRenderer.DrawRect({j * step_size, i * step_size}, {step_size, step_size}, Color(0.8f, 0.8, 0.8, 1.f), m_LoadingScreen);
            }
        }

        const char *loading_string = "Generating terrain...";
        int font_size = 30;
        auto string_size = m_UIRenderer.GetTextSize(loading_string, font_size);
        m_UIRenderer.DrawString(loading_string, font_size, {m_WindowSize.x/2 - string_size.x/2, m_WindowSize.y/2 - string_size.y/2});
    }
    m_UIRenderer.End();
    DisplayServer::Window.SwapBuffers();

    SceneManager::SetScene(std::make_unique<GameScene>());

}