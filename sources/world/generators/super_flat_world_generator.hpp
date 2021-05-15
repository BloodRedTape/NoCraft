#ifndef SUPER_FLAT_WORLD_GENERATOR_HPP
#define SUPER_FLAT_WORLD_GENERATOR_HPP

#include "world/chunk.hpp"
#include "core/math/vector2.hpp"
#include "utils/noise.hpp"
#include "world_generator.hpp"
#include "biome.hpp"

class SuperFlatWorldGenerator: public WorldGenerator{
private:
    u8 m_StoneLevel = 30;
    u8 m_SumMantleHeight = 3;
public:
    SuperFlatWorldGenerator(u64 seed){(void)seed;}

    virtual void Generate(Chunk &chunk, Vector2i coords)override;
};

#endif//SUPER_FLAT_WORLD_GENERATOR_HPP