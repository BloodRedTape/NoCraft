#include "platform/io.hpp"
#include "platform/clock.hpp"
#include "core/move.hpp"
#include "world_renderer.hpp"
#include "mesh_builder.hpp"

WorldRenderer::WorldRenderer(World *world):
    m_World(world)
{
    for(int i = -RenderDistance/2; i<RenderDistance/2 + 1; i++){
        for(int j = -RenderDistance/2; j<RenderDistance/2 + 1; j++){
            m_Chunks[RenderDistance/2 + i][RenderDistance/2 + j] = Move(MeshBuilder::Build(m_World->Get({i,j}),{i,0,j}));
        }
    }
}

void WorldRenderer::Render(const Camera &camera){
    auto position = GetChunkPos(camera.Position());

    auto offset = position - m_PrevCameraPos;

    m_PrevCameraPos = position;

    if(offset != Vector2i(0, 0)){
        Reswap(offset);
        //Println("Moved");
    }

    m_ChunkRenderer.BeginScene(camera);
    
    for(int i = 0; i<RenderDistance; i++){
        for(int j = 0; j<RenderDistance; j++){
            if(!m_Chunks[i][j].VertexBuffer.IsEmpty())
                m_ChunkRenderer.Draw(m_Chunks[i][j]);
        }
    }

    m_ChunkRenderer.EndScene();
}

void WorldRenderer::Reswap(Vector2i distance){
    Clock cl;
    Mesh old[RenderDistance][RenderDistance];

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
                m_Chunks[i][j] = MeshBuilder::Build(m_World->Get(cords), {cords.x, 0, cords.y});
            }
        }
    }

    for(int i = 0; i<RenderDistance; i++)
        for(int j = 0; j<RenderDistance; j++)
            old[i][j].Delete();
    Println(" ==== Reswap Took: % mcs", cl.GetElapsedTime().AsMicroseconds());
}

void WorldRenderer::Regenerate(Vector2i chunk_pos){
    auto index = chunk_pos - m_PrevCameraPos;
    int i = RenderDistance/2 + index.x;
    int j = RenderDistance/2 + index.y;
    auto cords = m_PrevCameraPos + Vector2i{i - RenderDistance/2,j-RenderDistance/2};
    m_Chunks[i][j].Delete();
    m_Chunks[i][j] = MeshBuilder::Build(m_World->Get(cords), {cords.x, 0, cords.y});
}

bool WorldRenderer::InDistance(Vector2i chunk_pos){
    return chunk_pos.x >= 0 && chunk_pos.x < RenderDistance && chunk_pos.y >= 0 && chunk_pos.y < RenderDistance; 
}