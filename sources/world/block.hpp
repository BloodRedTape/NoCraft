#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "platform/types.hpp"

using namespace StraitX;

enum class Block: u8{
    Air = 0,
    Grass,
    Dirt,
    Stone,
    Sand,
    OakLog,
    OakWood,
    Water,
    OakLeaves,
    Cactus,
    SpruceLog,
    SpruceLeaves,
    WinterGrass,
    BirchLog,
    BirchLeaves,
    Count
};

inline bool IsOpaque(Block block){
    if(block == Block::Air || block == Block::Water)
        return false;
    return true;
}

inline bool Exist(Block block){
    return block != Block::Air && block < Block::Count;
}


enum class BlockFace: u8 {
    Front,
    Back,
    Left,
    Right,
    Top,
    Bottom
};

struct BlockTextures{
    u8 Faces[6];
};

BlockTextures GetBlockTextures(Block block);

#endif//BLOCK_HPP