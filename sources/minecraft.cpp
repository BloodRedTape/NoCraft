#include "minecraft.hpp"
#include "main/engine.hpp"
#include "platform/io.hpp"
#include "platform/mouse.hpp"
#include "servers/display_server.hpp"
#include "platform/memory.hpp"


Result Minecraft::OnInitialize(){
    Mouse::SetVisible(false);
    Mouse::SetGlobalPosition({800,400});
    m_Player.Move({0, 40, 0});
    return Result::Success;
}

void Minecraft::OnUpdate(float dt){

    m_Player.Update(dt);

    if(Keyboard::IsKeyPressed(Key::Q))
        Stop();

    DisplayServer::Window.ClearColorBuffer(Color::LightBlue);
    DisplayServer::Window.ClearDepthBuffer();

    m_Renderer.Render(m_Player.GetCamera());


    m_UIRenderer.BeginScene(DisplayServer::Window.CurrentFramebuffer());
    auto size = DisplayServer::Window.Size();
    Vector2i pointer_size(20, 5);
    m_UIRenderer.DrawRect({size.width/2 - pointer_size.x/2, size.height/2 - pointer_size.y/2}, {pointer_size.x, pointer_size.y}, Color(0,0,0,0.5f));
    m_UIRenderer.DrawRect({size.width/2 - pointer_size.y/2, size.height/2 - pointer_size.x/2}, {pointer_size.y, pointer_size.x}, Color(0,0,0,0.5f));

    m_UIRenderer.EndScene();

    DisplayServer::Window.SwapBuffers();
}

bool Minecraft::OnEvent(const Event &e){
    if(e.Type == EventType::MouseButtonPress){
        if(e.MouseButtonPress.Button == Mouse::Left)
            m_Player.Dig(m_World, m_Renderer);
        if(e.MouseButtonPress.Button == Mouse::Right)
            m_Player.Place(m_World, m_Renderer);
        if(e.MouseButtonPress.Button == Mouse::Middle)
            m_Player.Pick(m_World);
    }
    return true;
}

void Minecraft::OnFinalize(){
    Mouse::SetVisible(true);
}