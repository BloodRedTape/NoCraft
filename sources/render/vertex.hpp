#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "core/math/vector3.hpp"
#include "core/math/vector2.hpp"
#include "graphics/api/graphics_pipeline.hpp"

using namespace StraitX;

struct Vertex{
    Vector3f a_Position;
    Vector2f a_TexCoord;
    Vector3f a_Normal;

    static VertexAttribute s_Attributes[3];
};


#endif//VERTEX_HPP