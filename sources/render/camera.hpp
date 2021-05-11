#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "core/math/matrix4.hpp"
#include "core/math/vector3.hpp"

using namespace StraitX;

class Camera{
private:
    Matrix4f m_Projection{1.0f};
    Vector3f m_Position;
    Vector3f m_Rotation;
public:
    void Move(Vector3f direction);

    void Rotate(Vector3f rotation);

    Vector3f Position()const{
        return -m_Position;
    }

    Vector3f Rotation()const{
        return -m_Rotation;
    }

    const Matrix4f &Projection()const;

    Matrix4f View()const;

    Matrix4f RotationMatrix()const;

    static Camera Perspective(float far, float near, float fov, float aspect);
};

#endif//CAMERA_HPP