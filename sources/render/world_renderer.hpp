#ifndef WORLD_RENDERER_HPP
#define WORLD_RENDERER_HPP

#include "solid_pass.hpp"
#include "reflect_pass.hpp"
#include "final_pass.hpp"
#include "graphics/api/framebuffer.hpp"
#include "core/push_array.hpp"
#include "world/world.hpp"
#include "camera.hpp"

class WorldRenderer{
private:
    Vector2i m_WindowSize;

    GPUTexture m_ViewAttachments[2];
    Sampler m_ViewSampler;
    Framebuffer *m_ViewFramebuffer;

    GPUTexture m_ReflectAttachments[2];
    Sampler m_ReflectSampler;
    Framebuffer *m_ReflectFramebuffer;

    SolidPass m_SolidPass;
    ReflectPass m_ReflectPass{m_SolidPass.Pass()};
    FinalPass m_FinalPass;

    World *m_World;

    static constexpr s32 RenderDistance = 21;

    Pair<Mesh, Mesh> m_Chunks[RenderDistance][RenderDistance];

    Vector2i m_PrevCameraPos;
public:
    WorldRenderer(World *world);

    void Render(Camera camera, int water_level);

    void Reswap(Vector2i distance);

    void Regenerate(Vector2i chunk_pos);

    bool InDistance(Vector2i chunk_pos);
};

#endif//WORLD_RENDERER_HPP
