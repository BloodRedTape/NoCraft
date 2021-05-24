#ifndef FINAL_PASS_HPP
#define FINAL_PASS_HPP

#include "graphics/render_window.hpp"
#include "graphics/api/sampler.hpp"
#include "graphics/api/graphics_pipeline.hpp"

using namespace StraitX;


struct Vertex2D{
    Vector2f a_Position;
    Vector2f a_TexCoords;
    float a_TexIndex;

    static VertexAttribute s_Attrs[3];
};

class FinalPass{
private:
    RenderWindow &m_Window;
    Vector2i m_WindowSize;
    Sampler m_ViewSampler;
    Sampler m_ReflectSampler;

    Shader *m_Shaders[2];
    GraphicsPipeline *m_Pipeline;

    GPUBuffer m_VertexBuffer;
    GPUBuffer m_IndexBuffer;
    u32 m_IndicesCount;
public:
    FinalPass();

    void Finish(GPUTexture *view_texture, GPUTexture *reflect_texture);
};

#endif//FINAL_PASS_HPP