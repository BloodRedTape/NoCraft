#include "platform/io.hpp"
#include "main_menu_scene.hpp"
#include "game_scene.hpp"
#include "render/render_2d.hpp"
#include "ui/ui.hpp"

MainMenuScene::MainMenuScene(){
    SamplerProperties props;
    props.MagFiltering = FilteringMode::Nearest;

    m_Background.LoadFromFile("resources/background.png");
    m_Logo.LoadFromFile("resources/logo.png");
    m_LoadingScreen.LoadFromFile("resources/dirt.png", props);
}

void MainMenuScene::OnUpdate(float dt){
    Render2D::Clear(Color(0.2, 0.2, 0.2, 1.0f));

    Render2D::DrawRect({0,0}, m_WindowSize, m_Background);
    Render2D::DrawRect({m_WindowSize.x/4, m_WindowSize.y/2}, {m_WindowSize.x/2, m_WindowSize.y/4}, m_Logo);


    VerticalLayout layout{{0, m_WindowSize.y/2}, {m_WindowSize.x, m_WindowSize.y/2}, {m_WindowSize.x/2, m_WindowSize.y / 10}, m_WindowSize.y / 40};

    if(layout.Button("Play")){
        OnPlayPressed();
    }

    std::string names[]={
        "World:  Natural ",
        "World:  Extreme ",
        "World: SuperFlat"
    };

    layout.Selector(names, m_CurrentGenerationType);

    if(layout.Button("Exit")){
        Stop();
    }
}

void MainMenuScene::OnPlayPressed(){
    
    float step_size = float(m_WindowSize.y)/15;

    for(int i = 0; i<m_WindowSize.y/step_size; i++){
        for(int j = 0; j<m_WindowSize.x/step_size; j++){
            Render2D::DrawRect({j * step_size, i * step_size}, {step_size, step_size}, Color(0.8f, 0.8, 0.8, 1.f), m_LoadingScreen);
        }
    }

    const char *loading_string = "Generating terrain...";
    int font_size = 30;
    auto string_size = UIRenderer::GetTextSize(loading_string, font_size);

    UIRenderer::DrawString(loading_string, font_size, {m_WindowSize.x/2 - string_size.x/2, m_WindowSize.y/2 - string_size.y/2});
    Render2D::Flush();
    Render2D::SwapBuffers();

    SceneManager::SetScene(std::make_unique<GameScene>(m_CurrentGenerationType));

}