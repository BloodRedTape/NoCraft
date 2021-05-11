#ifndef NATURAL_WORLD_GENERATOR_HPP
#define NATURAL_WORLD_GENERATOR_HPP

#include "world/chunk.hpp"
#include "core/math/vector2.hpp"
#include "utils/noise.hpp"
#include "world_generator.hpp"
#include "biome.hpp"

class NaturalWorldGenerator: public WorldGenerator{
private:
    static constexpr size_t s_WorldPower = 8;//13;
    static constexpr size_t s_GeneratorSize = 2 << s_WorldPower;
    NoiseGenerator2D<s_GeneratorSize> m_TerrainGenerator;
    NoiseGenerator2D<s_GeneratorSize> m_BiomeGenerator;
    RandomPlot2D<s_GeneratorSize> m_EntitiesPlot;

    u8 m_WaterLevel = 30;
    u8 m_GenerationSpan = 70;
    u8 m_SumMantleHeight = 3;
public:
    NaturalWorldGenerator(u64 seed);

    bool ShouldSpawnEntity(BiomeDefinition &def, Vector2i world_coords);

    virtual void Generate(Chunk &chunk, Vector2i coords)override;

    Biome GetBiome(Vector2i block_coords);

};

#endif//EXTREME_WORLD_GENERATOR_HPP