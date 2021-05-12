#ifndef INVENTORY_LAYER_HPP
#define INVENTORY_LAYER_HPP

#include "layers/base_ui_layer.hpp"

class InventoryLayer: public BaseUILayer{
private:
    Vector2i m_InventoryViewMargin{WindowSize.x * 0.1, WindowSize.y * 0.1};
    Vector2i m_InventoryViewSize{WindowSize.x - m_InventoryViewMargin.x * 2, WindowSize.y - m_InventoryViewMargin.y * 2};
public:
    void OnUpdate(float dt)override;

    void OnRender()override;
    
    bool OnEvent(const Event &e)override;
};

#endif//INVENTORY_LAYER_HPP