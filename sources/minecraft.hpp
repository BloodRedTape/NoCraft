#ifndef MINECRAFT_HPP
#define MINECRAFT_HPP

#include "main/application.hpp"

using namespace StraitX;

class Minecraft: public Application{
private:

public:
    Result OnInitialize()override;

    void OnUpdate(float dt)override;

    bool OnEvent(const Event &e)override;

    void OnFinalize()override;
};

#endif//MINECRAFT_HPP