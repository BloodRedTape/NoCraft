#include "world.hpp"
#include "platform/io.hpp"
#include <cmath>

namespace std{
    std::size_t hash<Vector2i>::operator()(const Vector2i &value)const noexcept{
        return hash<s32>{}(value.x) + hash<s32>{}(value.y) + (value.x << 2);
    }
}

World::World(std::unique_ptr<WorldGenerator> generator):
    m_Generator(std::move(generator))
{}


Chunk &World::Get(Vector2i chunk_coords){
    auto &chunk = GetEmpty(chunk_coords);

    if(!chunk.IsGenerated)
        m_Generator->Generate(chunk, chunk_coords);
    chunk.IsGenerated = true;

    return chunk;
}

Chunk &World::GetEmpty(Vector2i chunk_coords){
    auto chunk = m_Data.find(chunk_coords);

    if(chunk == m_Data.end()){
        auto new_chunk = m_Data.insert(std::pair<Vector2i, Chunk>(chunk_coords, {}));

        Assert(new_chunk.second && "Failed to insert a chunk");

        chunk = new_chunk.first;
    }
    return chunk->second;
}

Block World::GetBlock(Vector3f block_coords){
    block_coords.x = std::round(block_coords.x);
    block_coords.y = std::round(block_coords.y);
    block_coords.z = std::round(block_coords.z);

    Vector2i chunk_pos = GetChunkPos(block_coords);
    Chunk &chunk = Get(chunk_pos);
    Vector3i block_pos = Vector3i(block_coords.x - chunk_pos.x * Chunk::SizeX, block_coords.y, block_coords.z - chunk_pos.y * Chunk::SizeZ);

    return chunk.Get(block_pos);
}

void World::Place(Vector2i chunk_coords, Vector3i block_coords, Block block){
    auto &chunk = GetEmpty(chunk_coords);

    chunk.Set(block_coords, block);
}


void World::TryUnGet(Vector2i chunk_coords){
    auto chunk = m_Data.find(chunk_coords);

    Assert(chunk != m_Data.end());

    if(!chunk->second.IsModified){
        m_Data.erase(chunk);
        //Println("UnGot");
    }
}
