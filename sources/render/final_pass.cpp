#include "final_pass.hpp"
#include "servers/display_server.hpp"
#include "graphics/api/gpu_context.hpp"
#include "graphics/api/dma.hpp"
#include "core/log.hpp"


VertexAttribute Vertex2D::s_Attrs[3] = {
    VertexAttribute::Float2,
    VertexAttribute::Float2,
    VertexAttribute::Float,
};

Vertex2D s_Vertices[] = {
    {{ 1, 1},{1,1},0},
    {{ 1,-1},{1,0},0},
    {{-1, 1},{0,1},0},
    {{-1,-1},{0,0},0},

    {{  1, 1  },{1,1},1},
    {{  1, 0.5},{1,0},1},
    {{0.5, 1  },{0,1},1},
    {{0.5, 0.5},{0,0},1},
};

u32 s_Indices[]={
    0, 1, 2,
    3, 1, 2,

    4, 5, 6,
    7, 5, 6,
};

FinalPass::FinalPass():
    m_Window(DisplayServer::Window),
    m_WindowSize(m_Window.Size().width, m_Window.Size().height)
{
    m_ViewSampler.New({});
    m_ReflectSampler.New({});

    static const ShaderBinding bindings[1]={
        {
            0,
            2,
            ShaderBindingType::Sampler,
            Shader::Fragment
        }
    };

    m_Shaders[0] = Shader::New(Shader::Vertex,   Shader::Lang::GLSL, "shaders/final.vert.glsl");
    m_Shaders[1] = Shader::New(Shader::Fragment, Shader::Lang::GLSL, "shaders/final.frag.glsl");

    if(!m_Shaders[0]->IsValid() || !m_Shaders[0]->IsValid())
        LogError("FinalPass: Shaders are not valid");

    GraphicsPipelineProperties props;
    props.Shaders = {m_Shaders, lengthof(m_Shaders)};
    props.VertexAttributes = {Vertex2D::s_Attrs, lengthof(Vertex2D::s_Attrs)};
    props.Topology = PrimitivesTopology::Triangles;
    props.FramebufferViewport.x = 0;
    props.FramebufferViewport.y = 0;
    props.FramebufferViewport.Width = m_WindowSize.x;
    props.FramebufferViewport.Height = m_WindowSize.y;
    props.Rasterization = RasterizationMode::Fill;
    props.BlendFunc = BlendFunction::Add;
    props.SrcBlendFactor = BlendFactor::SrcAlpha;
    props.DstBlendFactor = BlendFactor::OneMinusSrcAlpha;
    props.Pass = m_Window.Pass();
    props.ShaderBindings = {bindings};

    m_Pipeline = GraphicsPipeline::New(props);

    if(!m_Pipeline->IsValid())
        LogError("FinalPass: pipeline is not valid");

    m_IndicesCount = lengthof(s_Indices);
    m_IndexBuffer.New(sizeof(s_Indices), GPUMemoryType::DynamicVRAM, GPUBuffer::IndexBuffer | GPUBuffer::TransferDestination);
    m_VertexBuffer.New(sizeof(s_Vertices), GPUMemoryType::DynamicVRAM, GPUBuffer::VertexBuffer| GPUBuffer::TransferDestination);

    DMA::Copy(s_Indices,  m_IndexBuffer);
    DMA::Copy(s_Vertices, m_VertexBuffer);
}

void FinalPass::Finish(GPUTexture *view_texture, GPUTexture *reflect_texture){
    GPUContext::Get()->Begin();
    {
        m_Pipeline->Bind(0,0, *view_texture, m_ViewSampler);
        m_Pipeline->Bind(0,1, *reflect_texture, m_ReflectSampler);

        GPUContext::Get()->Bind(m_Pipeline);

        GPUContext::Get()->BeginRenderPass(m_Window.Pass(), m_Window.CurrentFramebuffer());
        {
            GPUContext::Get()->BindVertexBuffer(m_VertexBuffer);
            GPUContext::Get()->BindIndexBuffer(m_IndexBuffer, IndicesType::Uint32);
            GPUContext::Get()->DrawIndexed(m_IndicesCount/2);
        }
        GPUContext::Get()->EndRenderPass();
    }
    GPUContext::Get()->End(); GPUContext::Get()->Submit();
}