#include "scene.hpp"

BaseScene::~BaseScene(){
    (void)0;
}

void BaseScene::OnUpdate(float dt){
    (void)dt;
}

bool BaseScene::OnEvent(const Event &e){
    (void)e;
    return false;
}

std::unique_ptr<BaseScene> SceneManager::s_CurrentScene;
std::unique_ptr<BaseScene> SceneManager::s_Candidate;