#ifndef WORLD_HPP
#define WORLD_HPP

#include <cmath>
#include <memory>
#include <unordered_map>
#include "core/math/vector2.hpp"
#include "chunk.hpp"
#include "world/generators/world_generator.hpp"

namespace std{
    template<>
    struct hash<Vector2i>{
        std::size_t operator()(const Vector2i &value)const noexcept;
    };
}

inline Vector2i GetChunkPos(const Vector3f &position){
    return {s32(round(position.x))/Chunk::SizeX + (position.x < 0 && s32(round(position.x))%Chunk::SizeX != 0 ? -1: 0), s32(round(position.z))/Chunk::SizeZ + (position.z < 0 && s32(round(position.z))%Chunk::SizeZ != 0 ? -1: 0)};
}

class World{
private:
    std::unordered_map<Vector2i, Chunk> m_Data;
    std::unique_ptr<WorldGenerator> m_Generator;//{12345};
public:
    World(std::unique_ptr<WorldGenerator> generator);

    Chunk &Get(Vector2i chunk_coords);

    Chunk &GetEmpty(Vector2i chunk_coords);

    void Place(Vector2i chunk_coords, Vector3i block_coords, Block block);

    void TryUnGet(Vector2i chunk_coords);
};

#endif//WORLD_HPP