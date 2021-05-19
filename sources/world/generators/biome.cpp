#include <algorithm>
#include "biome.hpp"

void BuildNothing(Chunk &chunk, Vector3i origin);
void BuildOakTree(Chunk &chunk, Vector3i origin);
void BuildBirchTree(Chunk &chunk, Vector3i origin);
void BuildSpruceTree(Chunk &chunk, Vector3i origin);
void BuildCactus(Chunk &chunk, Vector3i origin);

void BuildPyramid(Chunk &chunk, Vector3i origin);


BiomeDefinition s_BiomeTable[]={
    {
        Block::WinterGrass,
        Block::Dirt,
        80,
        &BuildSpruceTree,
        99990,
        &BuildNothing
    },
    {
        Block::Grass,
        Block::Dirt,
        50,
        &BuildBirchTree,
        99990,
        &BuildNothing
    },
    {
        Block::Sand,
        Block::Sand,
        200,
        &BuildCactus,
        10000,
        &BuildPyramid
    },
    {
        Block::Grass,
        Block::Dirt,
        50,
        &BuildOakTree,
        99990,
        &BuildNothing
    },
    {
        Block::Grass,
        Block::Dirt,
        200000,
        &BuildNothing,
        99990,
        &BuildNothing
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
        chunk.TrySet({origin.x, i, origin.z}, Block::Cactus);
}




void BuildPyramid(Chunk &chunk, Vector3i origin){
    int pyramid_height = 5;
    for(int i = 1; i<=pyramid_height; i++){
        for(int j = -i; j <= i; j++){
            for(int k = -i; k<=i; k++){
                chunk.TrySet(origin + Vector3i(j, pyramid_height - i, k), Block::Sand);
            }
        }
    }
    for(int j = -pyramid_height; j <= pyramid_height; j++){
        for(int k = -pyramid_height; k<=pyramid_height; k++){
            for(int i = origin.y-1; !IsOpaque(chunk.Get(Vector3i{j + origin.x, i, k + origin.z})) && i>0; i--)
                chunk.TrySet(Vector3i{j + origin.x, i, k + origin.z}, Block::Sand);
        }
    }
    chunk.TrySet(origin + Vector3i(0, pyramid_height, 0), Block::Sand);

    for(int i = -pyramid_height; i<=pyramid_height; i++){
        chunk.TrySet(origin + Vector3i(i, 0, 0), Block::Air);
        chunk.TrySet(origin + Vector3i(i, 1, 0), Block::Air);
    }
    chunk.TrySet(origin + Vector3i(-pyramid_height, 1, 1), Block::Sand);
    chunk.TrySet(origin + Vector3i(-pyramid_height, 1,-1), Block::Sand);
    chunk.TrySet(origin + Vector3i(-pyramid_height, 2, 0), Block::Sand);
    chunk.TrySet(origin + Vector3i(-pyramid_height + 1, 2, 0), Block::Sand);

    chunk.TrySet(origin + Vector3i( pyramid_height, 1, 1), Block::Sand);
    chunk.TrySet(origin + Vector3i( pyramid_height, 1,-1), Block::Sand);
    chunk.TrySet(origin + Vector3i( pyramid_height, 2, 0), Block::Sand);
    chunk.TrySet(origin + Vector3i( pyramid_height - 1, 2, 0), Block::Sand);

    for(int i = -pyramid_height; i<=pyramid_height; i++){
        chunk.TrySet(origin + Vector3i(0, 0, i), Block::Air);
        chunk.TrySet(origin + Vector3i(0, 1, i), Block::Air);
    }
    chunk.TrySet(origin + Vector3i(1, 1, -pyramid_height), Block::Sand);
    chunk.TrySet(origin + Vector3i(-1, 1,-pyramid_height), Block::Sand);
    chunk.TrySet(origin + Vector3i(0, 2, -pyramid_height), Block::Sand);
    chunk.TrySet(origin + Vector3i(0, 2, -pyramid_height + 1), Block::Sand);

    chunk.TrySet(origin + Vector3i(1, 1,  pyramid_height), Block::Sand);
    chunk.TrySet(origin + Vector3i(-1, 1, pyramid_height), Block::Sand);
    chunk.TrySet(origin + Vector3i(0, 2,  pyramid_height), Block::Sand);
    chunk.TrySet(origin + Vector3i(0, 2,  pyramid_height - 1), Block::Sand);
}


