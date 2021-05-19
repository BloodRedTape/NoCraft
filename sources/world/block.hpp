#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "platform/types.hpp"

using namespace StraitX;

enum class Block: u8{
    Air = 0,
    Grass,
    WinterGrass,
    Dirt,
    Stone,
    Coblestone,
    Sand,
    Cactus,
    Water,
    OakLog,
    OakWood,
    OakLeaves,
    SpruceLog,
    SpruceWood,
    SpruceLeaves,
    BirchLog,
    BirchWood,
    BirchLeaves,
    DiamondOre,
    GoldenOre,
    RedstoneOre,
    EmeraldOre,
    DiamondBlock,
    GoldenBlock,
    RedstoneBlock,
    EmeraldBlock,
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