#include "natural_world_generator.hpp"
#include "platform/io.hpp"
#include "platform/clock.hpp"
#include <algorithm>
#include <limits>

NaturalWorldGenerator::NaturalWorldGenerator(u64 seed):
    m_TerrainGenerator(seed),
    m_BiomeGenerator(seed * 2 + 14234),
    m_EntitiesPlot(seed/2 - 12345)
{}

Vector2<s64> GetChunkOffset(Vector2i chunk_coords){
    return Vector2<s64>(chunk_coords.x * Chunk::SizeX, chunk_coords.y * Chunk::SizeZ);
}

u8 NaturalWorldGenerator::GetWorldHeight(Vector2<s64> block_coords){
    return (m_TerrainGenerator.GetWrapped(block_coords.x, block_coords.y, 8) - 0.3)*m_GenerationSpan + m_WaterLevel;
}

Biome NaturalWorldGenerator::GetWorldBiome(Vector2<s64> block_coords){
    return Biome(m_BiomeGenerator.GetWrapped(block_coords.x, block_coords.y, 5) * (int)Biome::Count);
}

short NaturalWorldGenerator::GetEntityValue(Vector2<s64> block_coords){
    return m_EntitiesPlot.GetWrapped(block_coords.x, block_coords.y) * std::numeric_limits<short>::max();
}

void NaturalWorldGenerator::Generate(Chunk &chunk, Vector2i chunk_coords){
    Clock cl;
    auto offset = GetChunkOffset(chunk_coords);
    
    static Vector2<s64> offsets_normalized[]={
        { 1,-1}, 
        { 1, 0}, 
        { 1, 1},

        { 0,-1}, 
        { 0, 0}, 
        { 0, 1},

        {-1,-1},
        {-1, 0},
        {-1, 1}
    };

    static Vector2<s64> offsets[]={
        {Chunk::SizeX *  1, Chunk::SizeZ * -1}, 
        {Chunk::SizeX *  1, Chunk::SizeZ *  0}, 
        {Chunk::SizeX *  1, Chunk::SizeZ *  1}, 
                                           
        {Chunk::SizeX *  0, Chunk::SizeZ * -1}, 
        {Chunk::SizeX *  0, Chunk::SizeZ *  0}, 
        {Chunk::SizeX *  0, Chunk::SizeZ *  1}, 
                                           
        {Chunk::SizeX * -1, Chunk::SizeZ * -1},
        {Chunk::SizeX * -1, Chunk::SizeZ *  0},
        {Chunk::SizeX * -1, Chunk::SizeZ *  1},
    };

    u8 height_map[9][Chunk::SizeX][Chunk::SizeZ];
    for(int b = 0; b < 9; b++){
        for(int i = 0; i<Chunk::SizeX; i++)
            for(int j = 0; j<Chunk::SizeZ; j++)
                height_map[b][i][j] = GetWorldHeight(Vector2<s64>{offset.x + i,offset.y + j} + offsets[b]);
    }
    BiomeDefinition biome_map[9][Chunk::SizeX][Chunk::SizeZ];
    for(int b = 0; b < 9; b++){
        for(int i = 0; i<Chunk::SizeX; i++)
            for(int j = 0; j<Chunk::SizeZ; j++)
                biome_map[b][i][j] = GetDefinition(GetWorldBiome(Vector2<s64>{offset.x + i,offset.y + j} + offsets[b]));
    }
    for(int i = 0; i<Chunk::SizeY; i++){
        for(int j = 0; j<Chunk::SizeX; j++){
            for(int k = 0; k<Chunk::SizeZ; k++){
                auto height = height_map[4][j][k];
                auto &biome = biome_map[4][j][k];
                
                if(i < height && i >= height - m_SumMantleHeight)
                    chunk.Blocks[i][j][k] = biome.SubMantle;
                if(i == height && i > m_WaterLevel)
                    chunk.Blocks[i][j][k] = biome.Mantle;
                if(i < height - m_SumMantleHeight)
                    chunk.Blocks[i][j][k] = Block::Stone;
                if(i <= m_WaterLevel && chunk.Blocks[i][j][k] == Block::Air)
                    chunk.Blocks[i][j][k] = Block::Water;
            }

        }
    }


    for(int b = 0; b<lengthof(offsets_normalized); b++){
        for(int i = 0; i<Chunk::SizeX; i++){
            for(int j = 0; j<Chunk::SizeZ; j++){                    
                auto &biome = biome_map[b][i][j];
                auto &height = height_map[b][i][j];
                if(GetEntityValue(Vector2<s64>{offset.x + i, offset.y + j} + Vector2<s64>(offsets[b])) % biome.EntityChance == 1
                && height > m_WaterLevel)
                    biome.BuildEntityProc(chunk, Vector3i{i, height + 1, j} + Vector3i(offsets[b].x, 0, offsets[b].y));
            }
        }
    }
    Println("Chunk generating took: % mcs", cl.GetElapsedTime().AsMicroseconds());
}
