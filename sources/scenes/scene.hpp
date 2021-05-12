#ifndef BASE_SCENE_HPP
#define BASE_SCENE_HPP

#include <memory>
#include "platform/events.hpp"
#include "main/engine.hpp"

using namespace StraitX;

struct BaseScene{
    virtual ~BaseScene();

    virtual void OnUpdate(float dt);

    virtual bool OnEvent(const Event &e);

    void Stop(){
        Engine::Get().Stop();
    }
};


class SceneManager{
private:
    static std::unique_ptr<BaseScene> s_CurrentScene;
    static std::unique_ptr<BaseScene> s_Candidate;
public:
    static void SetScene(std::unique_ptr<BaseScene> scene){
        KillCurrent();
        s_CurrentScene = std::move(scene);
    }

    static void KillCurrent(){
        s_Candidate = std::move(s_CurrentScene);
    }

    static BaseScene *GetCurrentScene(){
        s_Candidate.reset();
        return s_CurrentScene.get();
    }
};

#endif//BASE_SCENE_HPP