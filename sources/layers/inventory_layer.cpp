#include "layers/inventory_layer.hpp"
#include "render/render_2d.hpp"
#include "render/ui_renderer.hpp"
#include "utils/rect.hpp"

InventoryLayer::InventoryLayer(Player *player):
    m_Player(player)
{}

void InventoryLayer::OnUpdate(float dt){
    
    int font = 50;
    static const char *title = "Select Item";
    auto string_size = UIRenderer::GetTextSize(title, font);

    //Render2D::DrawRect({0,0}, WindowSize, Color(0.2, 0.2, 0.2, 0.5f));
    int view_width = m_HorizontalItemsCount*m_ItemSize + m_ItemMargin*m_HorizontalItemsCount + m_ItemMargin;
    int view_height = m_ItemSize*m_VerticalItemsCount + m_ItemMargin*m_VerticalItemsCount + m_ItemMargin;
    Render2D::DrawRect({WindowSize.x/2 - view_width/2, WindowSize.y - m_TopMargin - view_height}, {view_width, view_height + string_size.y*2}, Color(0.0, 0.0, 0.0, 0.6f));

    UIRenderer::DrawString(title, font, {WindowSize.x/2 - string_size.x/2, WindowSize.y - m_TopMargin});

    for(int i = 0; i<(int)Block::Count; i++){
        auto tex = TextureAtlas::Get().GetTextureCoordsBase(GetBlockTextures(Block(i)).Faces[(int)BlockFace::Front]);

        Vector2f coords[4]={
            {tex.First.x,                   tex.First.y + tex.Second.y},
            {tex.First.x,                   tex.First.y},
            {tex.First.x + tex.Second.x,    tex.First.y},
            {tex.First.x + tex.Second.x,    tex.First.y + tex.Second.y},
        };

        int x = i % m_HorizontalItemsCount;
        int y = i / m_HorizontalItemsCount;

        Vector2i position = {WindowSize.x/2 - view_width/2 + x*m_ItemSize + x*m_ItemMargin + m_ItemMargin, WindowSize.y - m_TopMargin - string_size.y*2 - m_ItemMargin - y*m_ItemMargin - y*m_ItemSize};
        Vector2i size(m_ItemSize, m_ItemSize);

        Rect rect(position - m_ItemMargin/2, position + size + m_ItemMargin/2);
        if(rect.Contains(UIRenderer::MousePosition())){
            Render2D::DrawRect(rect.Position(), rect.Size(), Color(0.8, 0.8, 0.8, 0.5f));
            if(Mouse::IsButtonPressed(Mouse::Left))
                m_Player->Select(Block(i));
        }

        Render2D::DrawRect(position, size, TextureAtlas::Get().MainTexture, coords);
    }
}

void InventoryLayer::OnRender(){
    (void)0;
}
    
bool InventoryLayer::OnEvent(const Event &e){
    if(e.Type == EventType::KeyPress){
        if(e.KeyPress.KeyCode == Key::Escape || e.KeyPress.KeyCode == Key::E){
            PopSelf();
            return true;
        }
    }
    if(e.Type == EventType::MouseButtonPress)
        if(e.MouseButtonPress.Button == Mouse::Left)
            return true;
    return false;
}