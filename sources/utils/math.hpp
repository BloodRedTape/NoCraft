#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>
#include "core/math/matrix4.hpp"


using namespace StraitX;

constexpr float Pi = 3.1415926535;

constexpr float Rad(float degree){
    return degree / 180.f * Pi;
}

constexpr Matrix4f RotationX(float angle){
    Matrix4f res{1.f};
    res[1][1] = cos(angle);
    res[1][2] = sin(angle);
    res[2][2] = cos(angle);
    res[2][1] = -sin(angle);
    return res;
}

constexpr Matrix4f RotationY(float angle){
    Matrix4f res{1.f};
    res[0][0] = cos(angle);
    res[0][2] = sin(angle);
    res[2][2] = cos(angle);
    res[2][0] = -sin(angle);
    return res;
}

constexpr Matrix4f RotationZ(float angle){
    Matrix4f res{1.f};
    res[0][0] = cos(angle);
    res[0][1] = sin(angle);
    res[1][1] = cos(angle);
    res[1][0] = -sin(angle);
    return res;
}

#endif//MATH_HPP