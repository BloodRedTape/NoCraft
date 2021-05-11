#ifndef RAY_HPP
#define RAY_HPP

#include "core/math/vector3.hpp"

using namespace StraitX;

class Ray{
private:
    Vector3f m_Origin;
    float m_Distance;
    Vector3f m_Direction;
public:
    Ray(Vector3f origin, Vector3f direction):
        m_Origin(origin),
        m_Direction(direction)
    {}

    void Step(float distance){
        m_Distance += distance;
    }

    float Distance(){
        return m_Distance;
    }

    Vector3f Current()const{
        return m_Origin + m_Direction * m_Distance;
    }
};

#endif//RAY_HPP