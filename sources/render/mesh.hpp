#ifndef MESH_HPP
#define MESH_HPP

#include "graphics/api/gpu_buffer.hpp"

using namespace StraitX;

struct Mesh{
    GPUBuffer VertexBuffer;
    GPUBuffer IndexBuffer;
    u32 IndicesCount;

    Mesh() = default;

    Mesh(const void *vertex_data, int vertex_data_size, const void *index_data, int index_data_size);

    void New(const void *vertex_data, int vertex_data_size, const void *index_data, int index_data_size);

    void Delete(){
        VertexBuffer.Delete();
        IndexBuffer.Delete();
    }
};

#endif//MESH_HPP