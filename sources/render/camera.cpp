#include "camera.hpp"
#include "utils/math.hpp"

void Camera::Move(Vector3f direction){
    m_Position += -direction;
}

void Camera::Rotate(Vector3f rotation){
    m_Rotation += rotation;
    if(m_Rotation.x > 360)
        m_Rotation.x -= 360;    
    if(m_Rotation.y > 360)
        m_Rotation.y -= 360;
    if(m_Rotation.z > 360)
        m_Rotation.z -= 360;
}

const Matrix4f &Camera::Projection()const{
    return m_Projection;
}

Matrix4f Camera::View()const{
    Matrix4f view{1.f};
    view[3][0] = m_Position.x;
    view[3][1] = m_Position.y;
    view[3][2] = m_Position.z;

    return view * RotationMatrix();
}

Matrix4f Camera::RotationMatrix()const{
    return (((RotationZ(Rad(m_Rotation.z))) * RotationY(Rad(m_Rotation.y))) * RotationX(Rad(m_Rotation.x)));
}

Camera Camera::Perspective(float far, float near, float fov, float aspect){
    Camera result;
    result.m_Projection[0][0] = 1.0/(aspect * tan(fov/2));
    result.m_Projection[1][1] = 1.0/tan(fov/2);
    result.m_Projection[2][2] = -(far + near)/(far - near);
    result.m_Projection[2][3] = -(2 * far * near)/(far - near);
    result.m_Projection[3][2] = -1;
    return result;
}