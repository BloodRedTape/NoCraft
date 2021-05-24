#include "player.hpp"
#include "utils/ray.hpp"
#include "platform/keyboard.hpp"
#include "platform/io.hpp"
#include "platform/mouse.hpp"
#include "render/ui_renderer.hpp"
#include "render/render_2d.hpp"
#include "servers/display_server.hpp"

bool operator>=(const Vector3f &left, const Vector3f &right){
    return left.x >= right.x && left.y >= right.y && left.z >= right.z;
}

constexpr Vector3f Round(Vector3f vec, Vector3i round){
    return {round.x?std::round(vec.x):vec.x,round.y?std::round(vec.y):vec.y, round.z?std::round(vec.z):vec.z};
}

Player::Player(World *world):
    m_World(world),
    m_Renderer(world),
    m_WindowSize(DisplayServer::Window.Size().width, DisplayServer::Window.Size().height)
{
    m_Camera.Move({0, 40, 0});

    SamplerProperties props;
    props.MagFiltering = FilteringMode::Nearest;

    m_BarSlot.LoadFromFile("resources/bar_slot.png", props);
    m_BarSelector.LoadFromFile("resources/bar_selector.png", props);
}

void Player::OnUpdate(float dt){
    if(Keyboard::IsKeyPressed(Key::LeftShift))
        Move({0,-m_Speed * dt, 0});
    if(Keyboard::IsKeyPressed(Key::Space))
        Move({0, m_Speed * dt, 0});

    if(Keyboard::IsKeyPressed(Key::A))
        Move({-m_Speed * dt, 0, 0});
    if(Keyboard::IsKeyPressed(Key::D))
        Move({ m_Speed * dt, 0, 0});
    
    if(Keyboard::IsKeyPressed(Key::W))
        Move({0, 0, m_Speed * dt});
    if(Keyboard::IsKeyPressed(Key::S))
        Move({0, 0,-m_Speed * dt});


    auto pos = Mouse::GlobalPosition();
    auto offset = Vector2i{pos.x, pos.y} - MouseResetPosition();

    Mouse::SetGlobalPosition({MouseResetPosition().x, MouseResetPosition().y});

    m_Camera.Rotate(Vector3f(-offset.y, offset.x, 0)/(1/m_MouseSpeed));

              
    Vector3i face_direction[]={
        { 0, 0,-1},
        { 0, 0, 1},
        {-1, 0, 0},
        { 1, 0, 0},
        { 0, 1, 0},
        { 0,-2, 0}
    };

    Vector3f player_pos = (m_Camera.Position() - Vector3f(0, 1, 0)) + m_Movement;
    
    for(int i = 0; i<4; i++){
        if(IsOpaque(m_World->GetBlock(player_pos - Vector3f(face_direction[i]))) || IsOpaque(m_World->GetBlock(player_pos - Vector3f(face_direction[i]) + Vector3f(0, 1, 0)))){
            Vector3f face(face_direction[i]);
            auto block_coords = Round(player_pos, face_direction[i]);
            if(block_coords*face >= player_pos*face)
                m_Movement += block_coords - player_pos;
        }
    }

    for(int i = 4; i<6; i++){
        if(IsOpaque(m_World->GetBlock(player_pos - Vector3f(face_direction[i])))){
            Vector3f face(face_direction[i]);
            auto block_coords = Round(player_pos, face_direction[i]);
            if(block_coords*face >= player_pos*face)
                m_Movement += block_coords - player_pos;
        }
    }


    m_Camera.Move(m_Movement);
    m_Movement = {};
    Vector3f rounded = Round(m_Camera.Position(),{1,1,1});
    if(IsOpaque(m_World->GetBlock(rounded))){
        m_Camera.Move(rounded - m_Camera.Position());
    }
}

void Player::OnEvent(const Event &e){
    if(e.Type == EventType::MouseButtonPress){
        if(e.MouseButtonPress.Button == Mouse::Left)
            Dig();
        if(e.MouseButtonPress.Button == Mouse::Right)
            Place();
        if(e.MouseButtonPress.Button == Mouse::Middle)
            Pick();
    }

    if(e.Type == EventType::MouseWheel){
        m_Current = (m_Current - e.MouseWheel.Delta + s_InventorySize*10) % s_InventorySize;
    }
}

void Player::RenderPlayerView(){
    m_Renderer.Render(m_Camera, 30);
    RenderCursor();
    RenderBar();
    RenderDebugInfo();
}

void Player::RenderCursor(){
    auto pos = DisplayServer::Window.Size();
    m_WindowSize = {pos.width, pos.height};
    Vector2i pointer_size(20, 5);
    Render2D::DrawRect({m_WindowSize.x/2 - pointer_size.x/2, m_WindowSize.y/2 - pointer_size.y/2}, {pointer_size.x, pointer_size.y}, Color(0,0,0,0.5f));
    Render2D::DrawRect({m_WindowSize.x/2 - pointer_size.y/2, m_WindowSize.y/2 - pointer_size.x/2}, {pointer_size.y, pointer_size.x}, Color(0,0,0,0.5f));
}

void Player::RenderBar(){
    float x_beg = m_WindowSize.x/2.f - m_BarSize/2.f;
    for(int i = 0; i<s_InventorySize; i++){
        Render2D::DrawRect({x_beg,0}, {m_SlotSize, m_SlotSize}, m_BarSlot);

        auto tex = TextureAtlas::Get().GetTextureCoordsBase(GetBlockTextures(m_InventoryBar[i]).Faces[(int)BlockFace::Front]);

        Vector2f coords[4]={
            {tex.First.x,                   tex.First.y + tex.Second.y},
            {tex.First.x,                   tex.First.y},
            {tex.First.x + tex.Second.x,    tex.First.y},
            {tex.First.x + tex.Second.x,    tex.First.y + tex.Second.y},
        };
        auto offset = (m_SlotSize/20)*2;
        Render2D::DrawRect({x_beg + offset, offset}, {offset*8, offset*8}, TextureAtlas::Get().MainTexture, coords);

        if(i == m_Current)
            Render2D::DrawRect({x_beg,0}, {m_SlotSize, m_SlotSize}, m_BarSelector);
        x_beg+=m_SlotSize;
    }
}

void Player::RenderDebugInfo(){
    char buffer[30];
    BufferPrint(buffer,"Current: %", m_Current);
    UIRenderer::DrawString(buffer, 20, {0,0});

    char position[50];
    auto pos = m_Camera.Position();
    sprintf(position, "Position: x %.2f, y: %.2f, z: %.2f", pos.x, pos.y, pos.z);
    UIRenderer::DrawString(position, 20, {0, m_WindowSize.y - 20});
}

void Player::Select(Block block){
    m_InventoryBar[m_Current] = block;
}

void Player::Dig(){
    Vector4f dir = m_Camera.RotationMatrix() * Vector4f(0, 0, 1, 1);
    Vector3f direction(dir.x, dir.y, dir.z);//Vector3f(cos(Rad(m_Camera.Rotation().x)),cos(Rad(m_Camera.Rotation().y)),cos(Rad(m_Camera.Rotation().z)));

    for(Ray ray(m_Camera.Position(), direction); ray.Distance() < m_DigDistance; ray.Step(m_DigAccuracy)){
        auto current = ray.Current();
        auto chunk_pos = GetChunkPos(current);
        auto &chunk = m_World->Get(chunk_pos);


        auto in_chunk_pos = current - Vector3f(chunk_pos.x * Chunk::SizeX,0,chunk_pos.y * Chunk::SizeZ);
        
        auto rounded = Vector3i(round(in_chunk_pos.x),round(in_chunk_pos.y),round(in_chunk_pos.z));

        if(IsOpaque(chunk.Get(rounded))){
            chunk.Break(rounded);
            m_Renderer.Regenerate(chunk_pos);
            return;
        }
    }
}

void Player::Place(){
    Vector4f dir = m_Camera.RotationMatrix() * Vector4f(0, 0, 1, 1);
    Vector3f direction(dir.x, dir.y, dir.z);//Vector3f(cos(Rad(m_Camera.Rotation().x)),cos(Rad(m_Camera.Rotation().y)),cos(Rad(m_Camera.Rotation().z)));

    Chunk *prev_chunk = nullptr;
    Vector2i prev_chunk_pos;
    Vector3i prev_rounded;

    for(Ray ray(m_Camera.Position(), direction); ray.Distance() < m_DigDistance; ray.Step(m_DigAccuracy)){
        auto current = ray.Current();
        auto chunk_pos = GetChunkPos(current);
        auto &chunk = m_World->Get(chunk_pos);

        auto in_chunk_pos = current - Vector3f(chunk_pos.x * Chunk::SizeX,0,chunk_pos.y * Chunk::SizeZ);

        auto rounded = Vector3i(round(in_chunk_pos.x),round(in_chunk_pos.y),round(in_chunk_pos.z));

        if(IsOpaque(chunk.Get(rounded))){
            if(!prev_chunk)return;

            if(prev_rounded != Vector3i(Round(m_Camera.Position() - Vector3f(0, 0, 0), {1,1,1})) 
            && prev_rounded != Vector3i(Round(m_Camera.Position() - Vector3f(0, 1, 0), {1,1,1}))){
                prev_chunk->Place(prev_rounded, m_InventoryBar[m_Current]);
                m_Renderer.Regenerate(prev_chunk_pos);
            }
            return;
        }
        prev_chunk = &chunk;
        prev_chunk_pos = chunk_pos;
        prev_rounded = rounded;
    }
}

void Player::Pick(){
    Vector4f dir = m_Camera.RotationMatrix() * Vector4f(0, 0, 1, 1);
    Vector3f direction(dir.x, dir.y, dir.z);//Vector3f(cos(Rad(m_Camera.Rotation().x)),cos(Rad(m_Camera.Rotation().y)),cos(Rad(m_Camera.Rotation().z)));

    for(Ray ray(m_Camera.Position(), direction); ray.Distance() < m_DigDistance; ray.Step(m_DigAccuracy)){
        auto current = ray.Current();
        auto chunk_pos = GetChunkPos(current);
        auto &chunk = m_World->Get(chunk_pos);


        auto in_chunk_pos = current - Vector3f(chunk_pos.x * Chunk::SizeX,0,chunk_pos.y * Chunk::SizeZ);
        
        auto rounded = Vector3i(round(in_chunk_pos.x),round(in_chunk_pos.y),round(in_chunk_pos.z));

        if(IsOpaque(chunk.Get(rounded))){
            m_InventoryBar[m_Current] = chunk.Get(rounded);
            return;
        }
    }
}

void Player::Move(Vector3f direction){
    Vector4f new_dir = RotationY(Rad(-m_Camera.Rotation().y)) * Vector4f{direction.x, 0, direction.z, 0};

    //m_Camera.Move({new_dir.x, direction.y, new_dir.z});
    m_Movement += Vector3f(new_dir.x, direction.y, new_dir.z);
}

void Player::SetPosition(Vector3f position){
    m_Camera.Move(-m_Camera.Position() + position);
}