#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "block.hpp"
#include "core/math/vector3.hpp"
#include "core/math/vector2.hpp"
#include "core/pair.hpp"

using namespace StraitX;

struct Chunk{
    static constexpr s32 SizeX = 16;
    static constexpr s32 SizeY = 256;
    static constexpr s32 SizeZ = 16;

    Block Blocks[SizeY][SizeX][SizeZ]{};
    bool IsModified = false;
    bool IsGenerated = false;

    Block GetChecked(Vector3i index)const{
        if(index.x < SizeX && index.x >= 0
        && index.y < SizeY && index.y >= 0
        && index.z < SizeZ && index.z >= 0)
            return Get(index);
        else
            return Block::Air;
    }

    const Block &Get(Vector3i index)const{
        return Blocks[index.y][index.x][index.z];
    }

    void Set(Vector3i index, Block block){
        Get(index) = block;
        IsModified = true;
    }

    void Place(Vector3i index, Block block){
        Set(index, block);
    }

    void Break(Vector3i index){
        Set(index, Block::Air);
    }

    Block &Get(Vector3i index){
        return Blocks[index.y][index.x][index.z];
    }

    Block *TryGet(Vector3i index){
        if(index.x >= 0 && index.x < SizeX
        && index.y >= 0 && index.y < SizeY
        && index.z >= 0 && index.z < SizeZ)
            return &Get(index);
        else
            return nullptr;
    }

    void TrySet(Vector3i index, Block block){
        auto block_ptr = TryGet(index);
        if(block_ptr)
           *block_ptr = block;
    }
};

inline Pair<Vector2i, Vector3i> MapOutOfChunkScopeCoords(Vector3<s64> block_coords){
    Pair<Vector2i, Vector3i> result;

    result.First = Vector2i(block_coords.x/Chunk::SizeX + (block_coords.x < 0 && block_coords.x%Chunk::SizeX != 0 ? -1: 0), block_coords.z/Chunk::SizeZ + (block_coords.z < 0 && block_coords.z%Chunk::SizeZ != 0 ? -1: 0));
    result.Second = Vector3i(s32(block_coords.x - s32(result.First.x * Chunk::SizeX)), block_coords.y, s32(block_coords.z - s32(result.First.y * Chunk::SizeZ)));

    return result;
}
#endif//CHUNK_HPP