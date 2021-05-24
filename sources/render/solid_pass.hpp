#ifndef CHUNK_RENDERER_HPP
#define CHUNK_RENDERER_HPP

#include "core/math/vector3.hpp"
#include "graphics/api/graphics_pipeline.hpp"
#include "graphics/render_window.hpp"
#include "graphics/color.hpp"
#include "mesh.hpp"
#include "texture_atlas.hpp"
#include "camera.hpp"

using namespace StraitX;

class SolidPass{
private:
    struct Uniform{
        Matrix4f u_Projection;
        Matrix4f u_View;
        Vector4f u_ClippingPlane;
    };
private:
    RenderWindow &m_Window;
    Vector2u m_WindowSize;

    Shader *m_Shaders[2] = {};
    GraphicsPipeline *m_Pipeline = nullptr;
    RenderPass *m_Pass;

    CPUBuffer m_StagingUniform;
    GPUBuffer m_UniformBuffer;
public:
    SolidPass();

    ~SolidPass();

    void BeginScene(const Camera &camera, Vector4f clipping_plane, Framebuffer *framebuffer);

    void EndScene();

    void Draw(const Mesh &mesh);

    RenderPass *Pass(){
        return m_Pass;
    }
};

#endif//CHUNK_RENDERER_HPP