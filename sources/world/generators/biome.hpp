#ifndef BIOME_HPP
#define BIOME_HPP

#include "world/block.hpp"
#include "world/world.hpp"

enum class Biome: u8{
    Winter,
    BirchLand,
    Desert,
    Forest,
    FlatLand,
    Count
};


struct BiomeDefinition{
    Block Mantle;
    Block SubMantle;
    u32 EntityChance;
    void (*BuildEntityProc)(Chunk &world, Vector3i origin);
};


extern BiomeDefinition &GetDefinition(Biome biome);

#endif//BIOME_HPP