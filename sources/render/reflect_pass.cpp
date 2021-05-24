#include "reflect_pass.hpp"
#include "texture_atlas.hpp"
#include "servers/display_server.hpp"
#include "graphics/api/gpu_context.hpp"

ReflectPass::ReflectPass(RenderPass *view_fb_pass):
    m_Window(DisplayServer::Window),
    m_WindowSize(m_Window.Size().width, m_Window.Size().height),
    m_Pass(view_fb_pass)
{
    m_ReflectSampler.New({});

    static const ShaderBinding bindings[]={
        {0, 1, ShaderBindingType::Sampler,       Shader::Fragment},
        {1, 1, ShaderBindingType::Sampler,       Shader::Fragment},
        {2, 1, ShaderBindingType::UniformBuffer, Shader::Vertex}
    };

    m_Shaders[0] = Shader::New(Shader::Type::Vertex, Shader::Lang::GLSL, "shaders/reflect.vert.glsl");
    m_Shaders[1] = Shader::New(Shader::Type::Fragment, Shader::Lang::GLSL, "shaders/reflect.frag.glsl");

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

    m_VertexUniformBuffer.New(sizeof(VertexUniform), GPUMemoryType::DynamicVRAM, GPUBuffer::UniformBuffer | GPUBuffer::TransferDestination);
    m_FragmentUniformBuffer.New(sizeof(FragmentUniform), GPUMemoryType::DynamicVRAM, GPUBuffer::UniformBuffer | GPUBuffer::TransferDestination);

    m_StagingVertexUniform.New(m_VertexUniformBuffer.Size());
    m_StagingFragmentUniform.New(m_FragmentUniformBuffer.Size());
}

void ReflectPass::Begin(Framebuffer *view_framebuffer, GPUTexture *reflect_color_attachment, const Camera &camera){
    GPUContext::Get()->Begin();

    VertexUniform vert_uniform{
        camera.Projection(),
        camera.View()
    };

    FragmentUniform frag_uniform{
        Vector2f(m_WindowSize),
        camera.Position()
    };

    m_StagingVertexUniform.CopyData(&vert_uniform, sizeof(vert_uniform));
    GPUContext::Get()->Copy(m_StagingVertexUniform, m_VertexUniformBuffer);

    m_StagingFragmentUniform.CopyData(&frag_uniform, sizeof(frag_uniform));
    GPUContext::Get()->Copy(m_StagingFragmentUniform, m_FragmentUniformBuffer);

    m_Pipeline->Bind(0, 0, TextureAtlas::Get().MainTexture.GPUTexture, TextureAtlas::Get().MainTexture.Sampler);
    m_Pipeline->Bind(1, 0, *reflect_color_attachment, m_ReflectSampler);
    m_Pipeline->Bind(2, 0, m_FragmentUniformBuffer);
    m_Pipeline->Bind(3, 0, m_VertexUniformBuffer);

    GPUContext::Get()->Bind(m_Pipeline);

    GPUContext::Get()->BeginRenderPass(m_Pass, view_framebuffer);
}

void ReflectPass::DrawReflective(const Mesh &mesh){
    if(!mesh.IndicesCount)return;
    GPUContext::Get()->BindVertexBuffer(mesh.VertexBuffer);
    GPUContext::Get()->BindIndexBuffer(mesh.IndexBuffer, IndicesType::Uint32);
    GPUContext::Get()->DrawIndexed(mesh.IndicesCount);
}

void ReflectPass::End(){
    GPUContext::Get()->EndRenderPass();
    GPUContext::Get()->End(); GPUContext::Get()->Submit();
}