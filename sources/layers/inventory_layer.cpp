#include "layers/inventory_layer.hpp"
#include "render/render_2d.hpp"

void InventoryLayer::OnUpdate(float dt){
    (void)dt;
}

void InventoryLayer::OnRender(){
    Render2D::DrawRect({0,0}, WindowSize, Color(0.2, 0.2, 0.2, 0.5f));
    Render2D::DrawRect(m_InventoryViewMargin, m_InventoryViewSize, Color(0.8, 0.8, 0.8, 0.9f));
}
    
bool InventoryLayer::OnEvent(const Event &e){
    if(e.Type == EventType::KeyPress){
        if(e.KeyPress.KeyCode == Key::Escape || e.KeyPress.KeyCode == Key::E){
            PopSelf();
            return true;
        }
    }
    return false;
}