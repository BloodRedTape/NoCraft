#include "minecraft.hpp"
#include "main/engine.hpp"
#include "platform/io.hpp"
#include "platform/mouse.hpp"
#include "servers/display_server.hpp"
#include "platform/memory.hpp"

#include "scenes/main_menu_scene.hpp"

Result Minecraft::OnInitialize(){
    SceneManager::SetScene(std::make_unique<MainMenuScene>());
    return Result::Success;
}

void Minecraft::OnUpdate(float dt){
    SceneManager::GetCurrentScene()->OnUpdate(dt);
}

bool Minecraft::OnEvent(const Event &e){
    return SceneManager::GetCurrentScene()->OnEvent(e);
}

void Minecraft::OnFinalize(){
    SceneManager::KillCurrent();
}