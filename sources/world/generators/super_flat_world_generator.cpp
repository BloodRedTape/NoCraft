#include "super_flat_world_generator.hpp"
#include "platform/io.hpp"
#include "platform/clock.hpp"
#include <algorithm>
#include <limits>


void SuperFlatWorldGenerator::Generate(Chunk &chunk, Vector2i coords){
    Clock cl;

    for(int i = 0; i<Chunk::SizeY; i++){
        for(int j = 0; j<Chunk::SizeX; j++){
            for(int k = 0; k<Chunk::SizeZ; k++){
                
                if(i <= m_StoneLevel)
                    chunk.Blocks[i][j][k] = Block::Stone;
                else if(i <= m_StoneLevel + m_SumMantleHeight)
                    chunk.Blocks[i][j][k] = Block::Dirt;
                else if(i <= m_StoneLevel + m_SumMantleHeight + 1)
                    chunk.Blocks[i][j][k] = Block::Grass;
            }

        }
    }
    Println("Chunk generating took: % mcs", cl.GetElapsedTime().AsMicroseconds());
}
