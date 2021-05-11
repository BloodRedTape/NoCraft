#include "player.hpp"
#include "utils/ray.hpp"
#include "platform/keyboard.hpp"
#include "platform/io.hpp"
#include "platform/mouse.hpp"

void Player::Update(float dt){
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


    Vector2i global_position(800, 400);

    auto offset = Vector2i{Mouse::GlobalPosition().x, Mouse::GlobalPosition().y} - global_position;

    Mouse::SetGlobalPosition({global_position.x, global_position.y});

    m_Camera.Rotate(Vector3f(-offset.y, offset.x, 0)/(1/m_MouseSpeed));

    //Println("x: % y: % z: %", m_Camera.Rotation.x, m_Camera.Rotation.y, m_Camera.Rotation.z);

}

void Player::Dig(World &world, WorldRenderer &renderer){
    Vector4f dir = m_Camera.RotationMatrix() * Vector4f(0, 0, 1, 1);
    Vector3f direction(dir.x, dir.y, dir.z);//Vector3f(cos(Rad(m_Camera.Rotation().x)),cos(Rad(m_Camera.Rotation().y)),cos(Rad(m_Camera.Rotation().z)));

    for(Ray ray(m_Camera.Position(), direction); ray.Distance() < m_DigDistance; ray.Step(m_DigAccuracy)){
        auto current = ray.Current();
        auto chunk_pos = GetChunkPos(current);
        auto &chunk = world.Get(chunk_pos);


        auto in_chunk_pos = current - Vector3f(chunk_pos.x * Chunk::SizeX,0,chunk_pos.y * Chunk::SizeZ);
        
        auto rounded = Vector3i(round(in_chunk_pos.x),round(in_chunk_pos.y),round(in_chunk_pos.z));

        if(IsOpaque(chunk.Get(rounded))){
            chunk.Break(rounded);
            renderer.Regenerate(chunk_pos);
            return;
        }
    }
}

void Player::Place(World &world, WorldRenderer &renderer){
    Vector4f dir = m_Camera.RotationMatrix() * Vector4f(0, 0, 1, 1);
    Vector3f direction(dir.x, dir.y, dir.z);//Vector3f(cos(Rad(m_Camera.Rotation().x)),cos(Rad(m_Camera.Rotation().y)),cos(Rad(m_Camera.Rotation().z)));

    Chunk *prev_chunk = nullptr;
    Vector2i prev_chunk_pos;
    Vector3i prev_rounded;

    for(Ray ray(m_Camera.Position(), direction); ray.Distance() < m_DigDistance; ray.Step(m_DigAccuracy)){
        auto current = ray.Current();
        auto chunk_pos = GetChunkPos(current);
        auto &chunk = world.Get(chunk_pos);

        auto in_chunk_pos = current - Vector3f(chunk_pos.x * Chunk::SizeX,0,chunk_pos.y * Chunk::SizeZ);

        auto rounded = Vector3i(round(in_chunk_pos.x),round(in_chunk_pos.y),round(in_chunk_pos.z));

        if(IsOpaque(chunk.Get(rounded))){
            if(!prev_chunk)return;

            prev_chunk->Place(prev_rounded, m_Current);
            renderer.Regenerate(prev_chunk_pos);
            return;
        }
        prev_chunk = &chunk;
        prev_chunk_pos = chunk_pos;
        prev_rounded = rounded;
    }
}

void Player::Pick(World &world){
    Vector4f dir = m_Camera.RotationMatrix() * Vector4f(0, 0, 1, 1);
    Vector3f direction(dir.x, dir.y, dir.z);//Vector3f(cos(Rad(m_Camera.Rotation().x)),cos(Rad(m_Camera.Rotation().y)),cos(Rad(m_Camera.Rotation().z)));

    for(Ray ray(m_Camera.Position(), direction); ray.Distance() < m_DigDistance; ray.Step(m_DigAccuracy)){
        auto current = ray.Current();
        auto chunk_pos = GetChunkPos(current);
        auto &chunk = world.Get(chunk_pos);


        auto in_chunk_pos = current - Vector3f(chunk_pos.x * Chunk::SizeX,0,chunk_pos.y * Chunk::SizeZ);
        
        auto rounded = Vector3i(round(in_chunk_pos.x),round(in_chunk_pos.y),round(in_chunk_pos.z));

        if(IsOpaque(chunk.Get(rounded))){
            m_Current = chunk.Get(rounded);
            return;
        }
    }
}

void Player::Move(Vector3f direction){
    Vector4f new_dir = RotationY(Rad(-m_Camera.Rotation().y)) * Vector4f{direction.x, 0, direction.z, 0};

    m_Camera.Move({new_dir.x, direction.y, new_dir.z});
}