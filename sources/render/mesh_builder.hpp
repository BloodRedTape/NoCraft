#ifndef CHUNK_MESHER_HPP
#define CHUNK_MESHER_HPP

#include "mesh.hpp"
#include "world/chunk.hpp"
#include "core/pair.hpp"

struct ChunkMeshBuilder{
    static Pair<Mesh, Mesh> Build(const Chunk &chunk, Vector3i position);
};

#endif//CHUNK_MESHER_HPP