#include "mesh_builder.hpp"
#include "graphics/api/dma.hpp"
#include "platform/io.hpp"
#include "core/math/vector3.hpp"
#include "chunk_renderer.hpp"
#include "texture_atlas.hpp"
#include "platform/clock.hpp"
#include <vector>

enum Face{
    Front,
    Back,
    Left,
    Right,
    Top,
    Bottom
};

namespace {

Vector3f cube_positions[]={
    // Front
    {-0.5,-0.5,-0.5},
    { 0.5, 0.5,-0.5},
    {-0.5, 0.5,-0.5},
    { 0.5,-0.5,-0.5},

    // Back
    { 0.5,-0.5, 0.5},
    {-0.5, 0.5, 0.5},
    { 0.5, 0.5, 0.5},
    {-0.5,-0.5, 0.5},        

    //Left
    {-0.5,-0.5, 0.5},
    {-0.5, 0.5,-0.5},
    {-0.5, 0.5, 0.5},
    {-0.5,-0.5,-0.5},

    //Right
    { 0.5,-0.5,-0.5},
    { 0.5, 0.5, 0.5},
    { 0.5, 0.5,-0.5},
    { 0.5,-0.5, 0.5},
    
    //Top
    {-0.5, 0.5,-0.5},
    { 0.5, 0.5, 0.5},
    {-0.5, 0.5, 0.5},
    { 0.5, 0.5,-0.5},

    //Bottom
    {-0.5,-0.5, 0.5},
    { 0.5,-0.5,-0.5},
    {-0.5,-0.5,-0.5},
    { 0.5,-0.5, 0.5}
};

Vector3i face_direction[]={
    { 0, 0,-1},
    { 0, 0, 1},
    {-1, 0, 0},
    { 1, 0, 0},
    { 0, 1, 0},
    { 0,-1, 0}
};

constexpr size_t s_ChunkVolume = Chunk::SizeX * Chunk::SizeY * Chunk::SizeZ;

Vertex s_VertexBuildArray[s_ChunkVolume * 6 * 4];
size_t s_VertexBuildArraySize = 0;

void PushVertex(const Vertex &vertex){
    s_VertexBuildArray[s_VertexBuildArraySize++] = vertex;
}

u32 s_IndexBuildArray[s_ChunkVolume * 6 * 6];
size_t s_IndexBuildArraySize = 0;

void PushIndex(u32 index){
    s_IndexBuildArray[s_IndexBuildArraySize++] = index;
}

void PushFace(Block block, Face face, Vector3f offset){
    if(block == Block::Air)return;

    auto coords = TextureAtlas::Get().GetTextureCoordsBase(GetBlockTextures(block).Faces[face]);

    Vertex vertices[4];

    vertices[0].a_Position = cube_positions[face*4 + 0] + offset;
    vertices[1].a_Position = cube_positions[face*4 + 1] + offset;
    vertices[2].a_Position = cube_positions[face*4 + 2] + offset;
    vertices[3].a_Position = cube_positions[face*4 + 3] + offset;

    vertices[0].a_TexCoord = {coords.First.x,                 coords.First.y + coords.Second};
    vertices[1].a_TexCoord = {coords.First.x + coords.Second, coords.First.y};
    vertices[2].a_TexCoord = {coords.First.x,                 coords.First.y};
    vertices[3].a_TexCoord = {coords.First.x + coords.Second, coords.First.y + coords.Second};
    
    PushVertex(vertices[0]);
    PushVertex(vertices[1]);
    PushVertex(vertices[2]);
    PushVertex(vertices[3]);
}

}//namespace ::

Mesh MeshBuilder::Build(const Chunk &chunk, Vector3i position){
    s_VertexBuildArraySize = 0;
    s_IndexBuildArraySize = 0;
    Clock cl;
    position.x *= Chunk::SizeX;
    position.y *= Chunk::SizeY;
    position.z *= Chunk::SizeZ;

    for(int i = 0; i<Chunk::SizeY; i++){
        for(int j = 0; j<Chunk::SizeX; j++){
            for(int k = 0; k<Chunk::SizeZ; k++){
                auto block = chunk.Blocks[i][j][k];

                if(!Exist(block))continue;

                for(int f = 0; f<6; f++){
                    auto look_at = face_direction[f];

                    if(Exist(chunk.GetChecked({j + look_at.x,i + look_at.y,k + look_at.z})))continue;

                    PushFace(block, (Face)f, Vector3f(j,i,k) + Vector3f(position));
                }
            }
        }
    }

    for(u32 i = 0; i<s_VertexBuildArraySize / 4; i++){
        PushIndex(i * 4 + 0);
        PushIndex(i * 4 + 3);
        PushIndex(i * 4 + 1);
        PushIndex(i * 4 + 0);
        PushIndex(i * 4 + 1);
        PushIndex(i * 4 + 2);
    }

    Println("Mesh Building took % mcs", cl.GetElapsedTime().AsMicroseconds());
    return Mesh(s_VertexBuildArray, s_VertexBuildArraySize * sizeof(Vertex), s_IndexBuildArray, s_IndexBuildArraySize * sizeof(u32));
}
