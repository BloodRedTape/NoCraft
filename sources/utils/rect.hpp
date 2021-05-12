#ifndef RECT_HPP
#define RECT_HPP

#include "core/math/vector2.hpp"

using namespace StraitX;

struct Rect{
    Vector2i Begin;
    Vector2i End;

    Rect() = default;

    Rect(Vector2i begin, Vector2i end):
        Begin(begin),
        End(end)
    {}

    Vector2i Position(){
        return Begin;
    }

    Vector2i Size(){
        return End - Begin;
    }

    bool Contains(Vector2i point){
        if(Begin.x < point.x && End.x > point.x
        && Begin.y < point.y && End.y > point.y)
            return true;
        return false;
    }
};

#endif//RECT_HPP