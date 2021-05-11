#include "chunk_renderer.hpp"
#include "platform/io.hpp"
#include "servers/display_server.hpp"
#include "graphics/api/dma.hpp"
#include "graphics/api/gpu_context.hpp"
#include "world/block.hpp"

VertexAttribute Vertex::s_Attributes[]={
    VertexAttribute::Float3,
    VertexAttribute::Float2
};

ShaderBinding bindings[]={
    {0, 1, ShaderBindingType::Sampler,       Shader::Fragment},
    {1, 1, ShaderBindingType::UniformBuffer, Shader::Vertex}
};


ChunkRenderer::ChunkRenderer():
    m_Window(DisplayServer::Window),
    m_WindowSize(m_Window.Size().width, m_Window.Size().height)
{
    m_Shaders[0] = Shader::New(Shader::Type::Vertex, Shader::Lang::GLSL, "shaders/chunk.vert.glsl");
    m_Shaders[1] = Shader::New(Shader::Type::Fragment, Shader::Lang::GLSL, "shaders/chunk.frag.glsl");

    GraphicsPipelineProperties props;
    props.Shaders = {m_Shaders, lengthof(m_Shaders)};
    props.VertexAttributes = {Vertex::s_Attributes, lengthof(Vertex::s_Attributes)};
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
    props.ShaderBindings = {bindings, lengthof(bindings)};

    m_Pipeline = GraphicsPipeline::New(props);

    m_StagingUniform.New(sizeof(Uniform));
    m_UniformBuffer.New(sizeof(Uniform), GPUMemoryType::DynamicVRAM, GPUBuffer::UniformBuffer | GPUBuffer::TransferDestination);
}

ChunkRenderer::~ChunkRenderer(){
    GraphicsPipeline::Delete(m_Pipeline);

    Shader::Delete(m_Shaders[0]);
    Shader::Delete(m_Shaders[1]);
}

void ChunkRenderer::BeginScene(const Camera &camera){
    GPUContext::Get()->Begin();
    m_Pipeline->Bind(0, 0, TextureAtlas::Get().MainTexture.GPUTexture, TextureAtlas::Get().MainTexture.Sampler);
    m_Pipeline->Bind(1, 0, m_UniformBuffer);

    Uniform uniform{
        camera.Projection(),
        camera.View()
    };

    m_StagingUniform.CopyData(&uniform, sizeof(uniform));

    GPUContext::Get()->Copy(m_StagingUniform, m_UniformBuffer);

    GPUContext::Get()->Bind(m_Pipeline);

    GPUContext::Get()->BeginRenderPass(m_Window.Pass(), m_Window.CurrentFramebuffer());
}

void ChunkRenderer::EndScene(){

    GPUContext::Get()->EndRenderPass();
    GPUContext::Get()->End();GPUContext::Get()->Submit();
}

void ChunkRenderer::Draw(const Mesh &mesh){
    if(!mesh.IndicesCount)return;
    GPUContext::Get()->BindVertexBuffer(mesh.VertexBuffer);
    GPUContext::Get()->BindIndexBuffer(mesh.IndexBuffer, IndicesType::Uint32);
    GPUContext::Get()->DrawIndexed(mesh.IndicesCount);
}