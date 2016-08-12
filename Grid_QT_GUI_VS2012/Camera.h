#pragma once

#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>

#include <QObject>

class Camera : public QObject
{
Q_OBJECT

protected:
    glm::vec3 _pos;
    glm::vec3 _look_at;
    glm::vec3 _up;

    glm::mat4 _view_mat;
    glm::mat4 _proj_mat;

public:
    Camera() {};
    ~Camera() {};

    void LookAt(glm::vec3 eye, glm::vec3 lookat, glm::vec3 up);
    void Perspective(float fovy_rad, float aspect_ratio, float near, float far);
    void Frustum(float left, float right, float bottom, float top, float near, float far);
    void GlLoadMatrices();
};

class OrbitCamera : public Camera
{
public:
    void h_rotate(float rad);
    void v_rotate(float rad);
};
