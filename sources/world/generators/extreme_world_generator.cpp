#include "extreme_world_generator.hpp"
#include "platform/io.hpp"
#include "platform/clock.hpp"
#include <algorithm>
#include <limits>

ExtremeWorldGenerator::ExtremeWorldGenerator(u64 seed):
    m_TerrainGenerator(seed),
    m_BiomeGenerator(seed * 2 + 14234),
    m_EntitiesPlot(seed/2 - 12345)
{}

void ExtremeWorldGenerator::Generate(Chunk &chunk, Vector2i coords){
    Clock cl;
    u8 height_map[Chunk::SizeX][Chunk::SizeZ];
    auto offset = Vector2i(coords.x * Chunk::SizeX, coords.y * Chunk::SizeZ);
    for(int i = 0; i<Chunk::SizeX; i++)
        for(int j = 0; j<Chunk::SizeZ; j++)
            height_map[i][j] = m_TerrainGenerator.GetWrapped(offset.x + i - 42342,offset.y + j + 234234, 8)*255;
    
    BiomeDefinition biome_map[Chunk::SizeX][Chunk::SizeZ];
    for(int i = 0; i<Chunk::SizeX; i++)
        for(int j = 0; j<Chunk::SizeZ; j++)
            biome_map[i][j] = GetDefinition(GetBiome({offset.x + i + 23453,offset.y + j - 3453}));

    for(int i = 0; i<Chunk::SizeY; i++){
        for(int j = 0; j<Chunk::SizeX; j++){
            for(int k = 0; k<Chunk::SizeZ; k++){
                auto height = height_map[j][k] - 40;
                auto &generator = biome_map[j][k];
                
                if(i < height && i >= height - m_SumMantleHeight)
                    chunk.Blocks[i][j][k] = generator.SubMantle;
                if(i == height && i > m_WaterLevel){
                    chunk.Blocks[i][j][k] = generator.Mantle;
                    if(long(m_EntitiesPlot.GetWrapped(offset.x + j - 265434, offset.y + k + 354335) * std::numeric_limits<short>::max()) % generator.EntityChance == 1)
                        generator.BuildEntityProc(chunk, {j,i + 1, k});
                }
                if(i < height - m_SumMantleHeight)
                    chunk.Blocks[i][j][k] = Block::Stone;

                if(i <= m_WaterLevel && chunk.Blocks[i][j][k] == Block::Air)
                    chunk.Blocks[i][j][k] = Block::Water;
            }

        }
    }
    Println("Chunk generating took: % mcs", cl.GetElapsedTime().AsMicroseconds());
}

Biome ExtremeWorldGenerator::GetBiome(Vector2i block_coords){
    return Biome(m_BiomeGenerator.GetWrapped(block_coords.x, block_coords.y, 5) * (int)Biome::Count);
}

