#include "platform/io.hpp"
#include "platform/clock.hpp"
#include "core/move.hpp"
#include "world_renderer.hpp"
#include "mesh_builder.hpp"
#include "servers/display_server.hpp"

WorldRenderer::WorldRenderer(World *world):
    m_World(world),
    m_WindowSize(DisplayServer::Window.Size().width, DisplayServer::Window.Size().height)
{
    m_ViewAttachments[0].New(TextureFormat::RGBA8, GPUTexture::ColorAttachmentOptimal | GPUTexture::Sampled, m_WindowSize.x, m_WindowSize.y);
    m_ViewAttachments[1].New(TextureFormat::Depth32, GPUTexture::DepthStencilOptimal, m_WindowSize.x, m_WindowSize.y);

    const GPUTexture *view_attachments[2]={
        &m_ViewAttachments[0],
        &m_ViewAttachments[1],
    };

    m_ViewFramebuffer = Framebuffer::New(m_SolidPass.Pass(), {Vector2u(m_WindowSize), {view_attachments}});

    m_ReflectAttachments[0].New(TextureFormat::RGBA8, GPUTexture::ColorAttachmentOptimal | GPUTexture::Sampled, m_WindowSize.x, m_WindowSize.y);
    m_ReflectAttachments[1].New(TextureFormat::Depth32, GPUTexture::DepthStencilOptimal, m_WindowSize.x, m_WindowSize.y);

    const GPUTexture *reflect_attachments[2]={
        &m_ReflectAttachments[0],
        &m_ReflectAttachments[1],
    };

    m_ReflectFramebuffer = Framebuffer::New(m_SolidPass.Pass(), {Vector2u(m_WindowSize), {reflect_attachments}});

    for(int i = -RenderDistance/2; i<RenderDistance/2 + 1; i++){
        for(int j = -RenderDistance/2; j<RenderDistance/2 + 1; j++){
            m_Chunks[RenderDistance/2 + i][RenderDistance/2 + j] = Move(ChunkMeshBuilder::Build(m_World->Get({i,j}),{i,0,j}));
        }
    }
}

void WorldRenderer::Render(Camera camera, int water_level){
    auto position = GetChunkPos(camera.Position());

    auto offset = position - m_PrevCameraPos;

    m_PrevCameraPos = position;

    if(offset != Vector2i(0, 0)){
        Reswap(offset);
        //Println("Moved");
    }

    m_SolidPass.BeginScene(camera, Vector4f(0, 1, 0, 10000), m_ViewFramebuffer);
    {
        for(int i = 0; i<RenderDistance; i++){
            for(int j = 0; j<RenderDistance; j++){
                if(!m_Chunks[i][j].First.VertexBuffer.IsEmpty())
                    m_SolidPass.Draw(m_Chunks[i][j].First);
            }
        }
    }
    m_SolidPass.EndScene();

    auto above = 2*(camera.Position().y - water_level - 0.5);
    camera.Move({0, -above, 0});
    
    camera.ReflectInX();

    m_SolidPass.BeginScene(camera, Vector4f(0, 1, 0, -30), m_ReflectFramebuffer);
    {
        for(int i = 0; i<RenderDistance; i++){
            for(int j = 0; j<RenderDistance; j++){
                if(!m_Chunks[i][j].First.VertexBuffer.IsEmpty())
                    m_SolidPass.Draw(m_Chunks[i][j].First);
            }
        }
    }
    m_SolidPass.EndScene();


    camera.Move({0, above, 0});
    
    camera.ReflectInX();

    m_ReflectPass.Begin(m_ViewFramebuffer, &m_ReflectAttachments[0], camera);
        {
        for(int i = 0; i<RenderDistance; i++){
            for(int j = 0; j<RenderDistance; j++){
                if(!m_Chunks[i][j].Second.VertexBuffer.IsEmpty()){
                    m_ReflectPass.DrawReflective(m_Chunks[i][j].Second);
                }
            }
        }
    }
    m_ReflectPass.End();

    m_FinalPass.Finish(&m_ViewAttachments[0], &m_ReflectAttachments[0]);
}

void WorldRenderer::Reswap(Vector2i distance){
    Clock cl;
    Pair<Mesh, Mesh> old[RenderDistance][RenderDistance];

    for(int i = 0; i<RenderDistance; i++)
        for(int j = 0; j<RenderDistance; j++)
            old[i][j] = Move(m_Chunks[i][j]);

    for(int i = 0; i<RenderDistance; i++){
        for(int j = 0; j<RenderDistance; j++){
            auto candidate = Vector2i{i, j} + distance;
            if(!InDistance(Vector2i{i, j} - distance)){
                auto cords = m_PrevCameraPos - distance + Vector2i{i - RenderDistance/2,j-RenderDistance/2};
                m_World->TryUnGet(cords);
            }
            if(InDistance(Vector2i{i, j} + distance)){                    
                m_Chunks[i][j] = Move(old[candidate.x][candidate.y]);
            }else{
                auto cords = m_PrevCameraPos + Vector2i{i - RenderDistance/2,j-RenderDistance/2};
                m_Chunks[i][j] = ChunkMeshBuilder::Build(m_World->Get(cords), {cords.x, 0, cords.y});
            }
        }
    }

    for(int i = 0; i<RenderDistance; i++){
        for(int j = 0; j<RenderDistance; j++){
            old[i][j].First.Delete();
            old[i][j].Second.Delete();
        }
    }
    Println(" ==== Reswap Took: % mcs", cl.GetElapsedTime().AsMicroseconds());
}

void WorldRenderer::Regenerate(Vector2i chunk_pos){
    auto index = chunk_pos - m_PrevCameraPos;
    int i = RenderDistance/2 + index.x;
    int j = RenderDistance/2 + index.y;
    auto cords = m_PrevCameraPos + Vector2i{i - RenderDistance/2,j-RenderDistance/2};

    m_Chunks[i][j].First.Delete();
    m_Chunks[i][j].Second.Delete();

    m_Chunks[i][j] = ChunkMeshBuilder::Build(m_World->Get(cords), {cords.x, 0, cords.y});
}

bool WorldRenderer::InDistance(Vector2i chunk_pos){
    return chunk_pos.x >= 0 && chunk_pos.x < RenderDistance && chunk_pos.y >= 0 && chunk_pos.y < RenderDistance; 
}