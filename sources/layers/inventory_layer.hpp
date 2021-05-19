#ifndef INVENTORY_LAYER_HPP
#define INVENTORY_LAYER_HPP

#include "utils/layers.hpp"
#include "world/block.hpp"
#include "servers/display_server.hpp"
#include <cmath>
#include "player.hpp"

class InventoryLayer: public Layer{
private:
    Vector2i WindowSize{DisplayServer::Window.Size().width, DisplayServer::Window.Size().height};

    int m_HorizontalItemsCount = 9;
    int m_VerticalItemsCount = int(std::ceil(float(Block::Count)/m_HorizontalItemsCount));
    int m_ItemSize = WindowSize.x/18;
    int m_ItemMargin = m_ItemSize/2;

    int m_TopMargin = WindowSize.y/4;

    Player *m_Player;
public:
    InventoryLayer(Player *player);

    void OnUpdate(float dt)override;

    void OnRender()override;
    
    bool OnEvent(const Event &e)override;
};

#endif//INVENTORY_LAYER_HPP