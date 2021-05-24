#include "mesh_builder.hpp"
#include "graphics/api/dma.hpp"
#include "platform/io.hpp"
#include "core/math/vector3.hpp"
#include "vertex.hpp"
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

Vector3f cube_normals[]={
    { 0, 0,-1},
    { 0, 0, 1},
    {-1, 0, 0},
    { 1, 0, 0},
    { 0, 1, 0},
    { 0,-1, 0}
};

Vector3i face_direction[]={
    { 0, 0,-1},
    { 0, 0, 1},
    {-1, 0, 0},
    { 1, 0, 0},
    { 0, 1, 0},
    { 0,-1, 0}
};

template <size_t v_Count, size_t i_Count>
struct MeshBuilder{
    Vertex VertexBuildArray[v_Count];
    size_t VertexBuildArraySize = 0;

    u32 IndexBuildArray[i_Count];
    size_t IndexBuildArraySize = 0;

    void PushVertex(const Vertex &vertex){
        VertexBuildArray[VertexBuildArraySize++] = vertex;
    }

    void PushIndex(u32 index){
        IndexBuildArray[IndexBuildArraySize++] = index;
    }

    void FillIndices(){
        for(u32 i = 0; i<VertexBuildArraySize / 4; i++){
            PushIndex(i * 4 + 0);
            PushIndex(i * 4 + 3);
            PushIndex(i * 4 + 1);
            PushIndex(i * 4 + 0);
            PushIndex(i * 4 + 1);
            PushIndex(i * 4 + 2);
        }
    }

    void Reset(){
        VertexBuildArraySize = 0;
        IndexBuildArraySize = 0;
    }

    Mesh GetMesh(){
        return Mesh(VertexBuildArray, VertexBuildArraySize * sizeof(Vertex), IndexBuildArray, IndexBuildArraySize * sizeof(u32));
    }
};

constexpr size_t s_ChunkVolume = Chunk::SizeX * Chunk::SizeY * Chunk::SizeZ;

constexpr size_t s_VertexCount = s_ChunkVolume * 6 * 4;
constexpr size_t s_IndexCount = s_ChunkVolume * 6 * 6;

MeshBuilder<s_VertexCount, s_IndexCount> s_SolidBuilder;
MeshBuilder<s_VertexCount, s_IndexCount> s_ReflectBuilder;

void PushFace(MeshBuilder<s_VertexCount, s_IndexCount> &builder, Block block, Face face, Vector3f offset){
    if(block == Block::Air)return;

    auto coords = TextureAtlas::Get().GetTextureCoordsBase(GetBlockTextures(block).Faces[face]);

    Vertex vertices[4];

    vertices[0].a_Position = cube_positions[face*4 + 0] + offset;
    vertices[1].a_Position = cube_positions[face*4 + 1] + offset;
    vertices[2].a_Position = cube_positions[face*4 + 2] + offset;
    vertices[3].a_Position = cube_positions[face*4 + 3] + offset;

    vertices[0].a_TexCoord = {coords.First.x,                   coords.First.y + coords.Second.y};
    vertices[1].a_TexCoord = {coords.First.x + coords.Second.x, coords.First.y};
    vertices[2].a_TexCoord = {coords.First.x,                   coords.First.y};
    vertices[3].a_TexCoord = {coords.First.x + coords.Second.x, coords.First.y + coords.Second.y};

    vertices[0].a_Normal = cube_normals[face];
    vertices[1].a_Normal = cube_normals[face];
    vertices[2].a_Normal = cube_normals[face];
    vertices[3].a_Normal = cube_normals[face];
    
    builder.PushVertex(vertices[0]);
    builder.PushVertex(vertices[1]);
    builder.PushVertex(vertices[2]);
    builder.PushVertex(vertices[3]);
}

}//namespace ::

Pair<Mesh, Mesh> ChunkMeshBuilder::Build(const Chunk &chunk, Vector3i position){
    s_SolidBuilder.Reset();
    s_ReflectBuilder.Reset();

    Clock cl;
    position.x *= Chunk::SizeX;
    position.y *= Chunk::SizeY;
    position.z *= Chunk::SizeZ;

    for(int i = 0; i<Chunk::SizeY; i++){
        for(int j = 0; j<Chunk::SizeX; j++){
            for(int k = 0; k<Chunk::SizeZ; k++){
                auto block = chunk.Blocks[i][j][k];

                if(!Exist(block))continue;

                if(IsReflective(block)){
                    if(!Exist(chunk.GetChecked({j, i + 1, k})))
                        PushFace(s_ReflectBuilder, block, Face::Top, Vector3f(j,i,k) + Vector3f(position));
                }else{
                    for(int f = 0; f<6; f++){
                        auto look_at = face_direction[f];

                        if(IsOpaque(chunk.GetChecked({j + look_at.x,i + look_at.y,k + look_at.z})))continue;

                        PushFace(s_SolidBuilder, block, (Face)f, Vector3f(j,i,k) + Vector3f(position));
                    }
                }

            }
        }
    }

    s_SolidBuilder.FillIndices();
    s_ReflectBuilder.FillIndices();

    //Println("Mesh Building took % mcs", cl.GetElapsedTime().AsMicroseconds());
    return {s_SolidBuilder.GetMesh(), s_ReflectBuilder.GetMesh()};
}
