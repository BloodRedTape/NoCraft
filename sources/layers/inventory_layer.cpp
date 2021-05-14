#include "layers/inventory_layer.hpp"


void InventoryLayer::OnUpdate(float dt){
    (void)dt;
}

void InventoryLayer::OnRender(){
    UIRenderer.BeginScene(DisplayServer::Window.CurrentFramebuffer());
    {
        UIRenderer.DrawRect({0,0}, WindowSize, Color(0.2, 0.2, 0.2, 0.5f));
        UIRenderer.DrawRect(m_InventoryViewMargin, m_InventoryViewSize, Color(0.8, 0.8, 0.8, 0.9f));
    }
    UIRenderer.EndScene();
}
    
bool InventoryLayer::OnEvent(const Event &e){
    UIRenderer.HandleEvent(e);
    if(e.Type == EventType::KeyPress){
        if(e.KeyPress.KeyCode == Key::Escape || e.KeyPress.KeyCode == Key::E){
            PopSelf();
            return true;
        }
    }
    return false;
}