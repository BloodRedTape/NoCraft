#include "minecraft.hpp"
#include "main/engine.hpp"
#include "platform/io.hpp"
#include "platform/mouse.hpp"
#include "servers/display_server.hpp"
#include "render/render_2d.hpp"
#include "render/ui_renderer.hpp"
#include "ui/ui.hpp"
#include "platform/memory.hpp"

#include "scenes/main_menu_scene.hpp"

Result Minecraft::OnInitialize(){
    Render2D::Init();
    UIRenderer::Init();

    SceneManager::SetScene(std::make_unique<MainMenuScene>());

    return Result::Success;
}

void Minecraft::OnUpdate(float dt){
    if(Keyboard::IsKeyPressed(Key::Q))
        Stop();
    Render2D::Begin();
    {

        SceneManager::GetCurrentScene()->OnUpdate(dt);

    }
    Render2D::End(); Render2D::SwapBuffers();
    UI::ResetUIState();
}

bool Minecraft::OnEvent(const Event &e){
    UI::SetUIState(e);

    return SceneManager::GetCurrentScene()->OnEvent(e);
}

void Minecraft::OnFinalize(){
    SceneManager::KillCurrent();
}