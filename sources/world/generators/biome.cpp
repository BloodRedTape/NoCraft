#include <algorithm>
#include "biome.hpp"

void BuildNothing(Chunk &chunk, Vector3i origin);
void BuildOakTree(Chunk &chunk, Vector3i origin);
void BuildBirchTree(Chunk &chunk, Vector3i origin);
void BuildSpruceTree(Chunk &chunk, Vector3i origin);
void BuildCactus(Chunk &chunk, Vector3i origin);

BiomeDefinition s_BiomeTable[]={
    {
        Block::Grass,
        Block::Dirt,
        200000,
        &BuildNothing
    },
    {
        Block::Grass,
        Block::Dirt,
        50,
        &BuildBirchTree
    },
    {
        Block::Grass,
        Block::Dirt,
        50,
        &BuildOakTree
    },
    {
        Block::Sand,
        Block::Sand,
        200,
        &BuildCactus
    },
    {
        Block::WinterGrass,
        Block::Dirt,
        80,
        &BuildSpruceTree
    },
};

BiomeDefinition &GetDefinition(Biome biome){
    return s_BiomeTable[(size_t)biome];
}

void BuildNothing(Chunk &chunk, Vector3i origin){
    (void)chunk;
    (void)origin;
}



void BuildSimpleTree(Chunk &chunk, Vector3i origin, Block log, Block leaves, int tree_height){
    for(int i = 0; i<tree_height; i++)
        chunk.TrySet({origin.x, origin.y + i, origin.z}, log);
    
    chunk.TrySet({origin.x, origin.y + tree_height, origin.z}, leaves);

    chunk.TrySet({origin.x, origin.y + tree_height, origin.z + 1}, leaves);
    chunk.TrySet({origin.x, origin.y + tree_height, origin.z - 1}, leaves);
    chunk.TrySet({origin.x + 1, origin.y + tree_height, origin.z}, leaves);
    chunk.TrySet({origin.x - 1, origin.y + tree_height, origin.z}, leaves);


    chunk.TrySet({origin.x,     origin.y + tree_height - 1, origin.z + 1}, leaves);
    chunk.TrySet({origin.x,     origin.y + tree_height - 1, origin.z - 1}, leaves);
    chunk.TrySet({origin.x + 1, origin.y + tree_height - 1, origin.z}, leaves);
    chunk.TrySet({origin.x - 1, origin.y + tree_height - 1, origin.z}, leaves);
    chunk.TrySet({origin.x + 1, origin.y + tree_height - 1, origin.z + 1}, leaves);
    chunk.TrySet({origin.x - 1, origin.y + tree_height - 1, origin.z - 1}, leaves);
    chunk.TrySet({origin.x + 1, origin.y + tree_height - 1, origin.z - 1}, leaves);
    chunk.TrySet({origin.x - 1, origin.y + tree_height - 1, origin.z + 1}, leaves);
    
    chunk.TrySet({origin.x,     origin.y + tree_height - 2, origin.z + 1}, leaves);
    chunk.TrySet({origin.x,     origin.y + tree_height - 2, origin.z - 1}, leaves);
    chunk.TrySet({origin.x + 1, origin.y + tree_height - 2, origin.z}, leaves);
    chunk.TrySet({origin.x - 1, origin.y + tree_height - 2, origin.z}, leaves);
    chunk.TrySet({origin.x + 1, origin.y + tree_height - 2, origin.z + 1}, leaves);
    chunk.TrySet({origin.x - 1, origin.y + tree_height - 2, origin.z - 1}, leaves);
    chunk.TrySet({origin.x + 1, origin.y + tree_height - 2, origin.z - 1}, leaves);
    chunk.TrySet({origin.x - 1, origin.y + tree_height - 2, origin.z + 1}, leaves);
}

void BuildOakTree(Chunk &chunk, Vector3i origin){
    BuildSimpleTree(chunk, origin, Block::OakLog, Block::OakLeaves, 5);
}
void BuildBirchTree(Chunk &chunk, Vector3i origin){
    BuildSimpleTree(chunk, origin, Block::BirchLog, Block::BirchLeaves, 4);
}

void BuildSpruceTree(Chunk &chunk, Vector3i origin){

    int tree_height = 6;
    for(int i = 0; i<tree_height; i++)
        chunk.TrySet({origin.x, origin.y + i, origin.z}, Block::SpruceLog);
    
    chunk.TrySet({origin.x, origin.y + tree_height + 1, origin.z}, Block::SpruceLeaves);

    chunk.TrySet({origin.x, origin.y + tree_height, origin.z}, Block::SpruceLeaves);

    chunk.TrySet({origin.x, origin.y + tree_height, origin.z + 1}, Block::SpruceLeaves);
    chunk.TrySet({origin.x, origin.y + tree_height, origin.z - 1}, Block::SpruceLeaves);
    chunk.TrySet({origin.x + 1, origin.y + tree_height, origin.z}, Block::SpruceLeaves);
    chunk.TrySet({origin.x - 1, origin.y + tree_height, origin.z}, Block::SpruceLeaves);

    chunk.TrySet({origin.x, origin.y + tree_height - 2, origin.z + 1}, Block::SpruceLeaves);
    chunk.TrySet({origin.x, origin.y + tree_height - 2, origin.z - 1}, Block::SpruceLeaves);
    chunk.TrySet({origin.x + 1, origin.y + tree_height - 2, origin.z}, Block::SpruceLeaves);
    chunk.TrySet({origin.x - 1, origin.y + tree_height - 2, origin.z}, Block::SpruceLeaves);


    chunk.TrySet({origin.x,     origin.y + tree_height - 3, origin.z + 1}, Block::SpruceLeaves);
    chunk.TrySet({origin.x,     origin.y + tree_height - 3, origin.z - 1}, Block::SpruceLeaves);
    chunk.TrySet({origin.x + 1, origin.y + tree_height - 3, origin.z}, Block::SpruceLeaves);
    chunk.TrySet({origin.x - 1, origin.y + tree_height - 3, origin.z}, Block::SpruceLeaves);
    chunk.TrySet({origin.x + 1, origin.y + tree_height - 3, origin.z + 1}, Block::SpruceLeaves);
    chunk.TrySet({origin.x - 1, origin.y + tree_height - 3, origin.z - 1}, Block::SpruceLeaves);
    chunk.TrySet({origin.x + 1, origin.y + tree_height - 3, origin.z - 1}, Block::SpruceLeaves);
    chunk.TrySet({origin.x - 1, origin.y + tree_height - 3, origin.z + 1}, Block::SpruceLeaves);

    chunk.TrySet({origin.x,     origin.y + tree_height - 5, origin.z + 1}, Block::SpruceLeaves);
    chunk.TrySet({origin.x,     origin.y + tree_height - 5, origin.z - 1}, Block::SpruceLeaves);
    chunk.TrySet({origin.x + 1, origin.y + tree_height - 5, origin.z}, Block::SpruceLeaves);
    chunk.TrySet({origin.x - 1, origin.y + tree_height - 5, origin.z}, Block::SpruceLeaves);
    chunk.TrySet({origin.x + 1, origin.y + tree_height - 5, origin.z + 1}, Block::SpruceLeaves);
    chunk.TrySet({origin.x - 1, origin.y + tree_height - 5, origin.z - 1}, Block::SpruceLeaves);
    chunk.TrySet({origin.x + 1, origin.y + tree_height - 5, origin.z - 1}, Block::SpruceLeaves);
    chunk.TrySet({origin.x - 1, origin.y + tree_height - 5, origin.z + 1}, Block::SpruceLeaves);
}

void BuildCactus(Chunk &chunk, Vector3i origin){

    int cactus_height = 3;

    for(int i = origin.y; i<std::min(256, origin.y + cactus_height); i++)
        chunk.Set({origin.x, i, origin.z}, Block::Cactus);
}

