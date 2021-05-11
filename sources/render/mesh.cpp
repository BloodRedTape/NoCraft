#include "mesh.hpp"
#include "graphics/api/cpu_buffer.hpp"
#include "graphics/api/dma.hpp"
#include "platform/io.hpp"
#include "platform/clock.hpp"

Mesh::Mesh(const void *vertex_data, int vertex_data_size, const void *index_data, int index_data_size){
    New(vertex_data, vertex_data_size, index_data, index_data_size);
}

void Mesh::New(const void *vertex_data, int vertex_data_size, const void *index_data, int index_data_size){
    Clock cl;
    VertexBuffer.New(vertex_data_size, GPUMemoryType::DynamicVRAM, GPUBuffer::VertexBuffer | GPUBuffer::TransferDestination);
    IndexBuffer.New(index_data_size, GPUMemoryType::DynamicVRAM, GPUBuffer::IndexBuffer | GPUBuffer::TransferDestination);

    DMA::Copy(vertex_data, VertexBuffer, vertex_data_size);
    DMA::Copy(index_data, IndexBuffer, index_data_size);
    
    Assert(index_data_size % sizeof(u32) == 0);
    IndicesCount = index_data_size / sizeof(u32);

    Println("Mesh uploading took % mcs", cl.GetElapsedTime().AsMicroseconds());
}