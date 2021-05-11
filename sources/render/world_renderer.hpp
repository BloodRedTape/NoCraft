#ifndef WORLD_RENDERER_HPP
#define WORLD_RENDERER_HPP

#include "chunk_renderer.hpp"
#include "core/push_array.hpp"
#include "world/world.hpp"
#include "camera.hpp"

class WorldRenderer{
private:
    ChunkRenderer m_ChunkRenderer;
    World *m_World;

    static constexpr s32 RenderDistance = 21;

    Mesh m_Chunks[RenderDistance][RenderDistance];

    Vector2i m_PrevCameraPos;
public:
    WorldRenderer(World *world);

    void Render(const Camera &camera);

    void Reswap(Vector2i distance);

    void Regenerate(Vector2i chunk_pos);

    bool InDistance(Vector2i chunk_pos);
};

#endif//WORLD_RENDERER_HPP
