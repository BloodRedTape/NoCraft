#ifndef IGENERATOR_HPP
#define IGENERATOR_HPP

#include "core/math/vector2.hpp"
#include "world/chunk.hpp"

class WorldGenerator{
public:
    virtual void Generate(Chunk &chunk, Vector2i coords) = 0;
};


#endif//IGENERATOR_HPP