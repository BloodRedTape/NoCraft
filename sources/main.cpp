#include "minecraft.hpp"

ApplicationConfig GetApplicationConfig(){
    return {
        "Minecraft",
        GraphicsAPI::OpenGL,
        {
            2,
            SamplePoints::Samples_1,
            TextureFormat::Depth32
        },
        {1280, 720}
    };
}

Application *StraitXMain(){
    return new Minecraft;
}

void StraitXExit(Application *app){
    delete app;
}