#ifndef REFLECT_PASS_HPP
#define REFLECT_PASS_HPP

#include "vertex.hpp"
#include "graphics/render_window.hpp"
#include "graphics/api/graphics_pipeline.hpp"
#include "graphics/api/framebuffer.hpp"
#include "graphics/api/gpu_texture.hpp"
#include "camera.hpp"
#include "mesh.hpp"

class ReflectPass{
private:
    struct VertexUniform{
        Matrix4f u_Projection;
        Matrix4f u_View;
    };
    struct FragmentUniform{
        Vector2f u_WindowSize;
        Vector3f u_CameraPosition;
    };
private:
    RenderWindow &m_Window;
    Vector2i m_WindowSize;

    Shader *m_Shaders[2];
    GraphicsPipeline *m_Pipeline;
    
    CPUBuffer m_StagingVertexUniform;
    CPUBuffer m_StagingFragmentUniform;

    GPUBuffer m_VertexUniformBuffer;
    GPUBuffer m_FragmentUniformBuffer;

    RenderPass *m_Pass;

    Sampler m_ReflectSampler;
public:
    ReflectPass(RenderPass *view_fb_pass);

    void Begin(Framebuffer *view_framebuffer, GPUTexture *reflect_color_attachment, const Camera &camera);

    void DrawReflective(const Mesh &mesh);

    void End();
};


#endif//REFLECT_PASS_HPP