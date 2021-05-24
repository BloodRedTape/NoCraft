#include "solid_pass.hpp"
#include "platform/io.hpp"
#include "servers/display_server.hpp"
#include "graphics/api/dma.hpp"
#include "graphics/api/gpu_context.hpp"
#include "world/block.hpp"
#include "vertex.hpp"
#include "platform/types.hpp"


ShaderBinding bindings[]={
    {0, 1, ShaderBindingType::Sampler,       Shader::Fragment},
    {1, 1, ShaderBindingType::UniformBuffer, Shader::Vertex}
};

SolidPass::SolidPass():
    m_Window(DisplayServer::Window),
    m_WindowSize(m_Window.Size().width, m_Window.Size().height)
{
    static const AttachmentDescription attachments[]={
        {
            GPUTexture::Layout::ColorAttachmentOptimal,
            GPUTexture::Layout::ColorAttachmentOptimal,
            GPUTexture::Layout::ColorAttachmentOptimal,
            TextureFormat::RGBA8,
            SamplePoints::Samples_1
        },
        {
            GPUTexture::Layout::DepthStencilAttachmentOptimal,
            GPUTexture::Layout::DepthStencilAttachmentOptimal,
            GPUTexture::Layout::DepthStencilAttachmentOptimal,
            TextureFormat::Depth32,
            SamplePoints::Samples_1
        }
    };

    m_Pass = RenderPass::New({{attachments}});


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
    props.Pass = m_Pass;
    props.ShaderBindings = {bindings, lengthof(bindings)};

    m_Pipeline = GraphicsPipeline::New(props);

    m_StagingUniform.New(sizeof(Uniform));
    m_UniformBuffer.New(sizeof(Uniform), GPUMemoryType::DynamicVRAM, GPUBuffer::UniformBuffer | GPUBuffer::TransferDestination);
}

SolidPass::~SolidPass(){
    GraphicsPipeline::Delete(m_Pipeline);

    Shader::Delete(m_Shaders[0]);
    Shader::Delete(m_Shaders[1]);
}

void SolidPass::BeginScene(const Camera &camera, Vector4f clipping_plane, Framebuffer *framebuffer){
    GPUContext::Get()->Begin();

    GPUContext::Get()->ClearFramebufferColorAttachments(framebuffer, {Color::LightBlue.R, Color::LightBlue.G, Color::LightBlue.B, Color::LightBlue.A});
    GPUContext::Get()->ClearFramebufferDepthAttachments(framebuffer, 1.f);
    
    m_Pipeline->Bind(0, 0, TextureAtlas::Get().MainTexture.GPUTexture, TextureAtlas::Get().MainTexture.Sampler);
    m_Pipeline->Bind(1, 0, m_UniformBuffer);

    Uniform uniform{
        camera.Projection(),
        camera.View(),
        clipping_plane
    };

    m_StagingUniform.CopyData(&uniform, sizeof(uniform));

    GPUContext::Get()->Copy(m_StagingUniform, m_UniformBuffer);

    GPUContext::Get()->Bind(m_Pipeline);

    GPUContext::Get()->BeginRenderPass(m_Pass, framebuffer);
}

void SolidPass::EndScene(){

    GPUContext::Get()->EndRenderPass();
    GPUContext::Get()->End();GPUContext::Get()->Submit();
}

void SolidPass::Draw(const Mesh &mesh){
    if(!mesh.IndicesCount)return;
    GPUContext::Get()->BindVertexBuffer(mesh.VertexBuffer);
    GPUContext::Get()->BindIndexBuffer(mesh.IndexBuffer, IndicesType::Uint32);
    GPUContext::Get()->DrawIndexed(mesh.IndicesCount);
}