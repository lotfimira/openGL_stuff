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

signals:
    void changed();
};

class OrbitCamera : public Camera
{
Q_OBJECT

protected:
    glm::vec3 _center;
    float _radius;
    float _angle_h; // angles in radians
    float _angle_v;

public:
    OrbitCamera(): _radius(0), _angle_h(0), _angle_v(0){}
    void setCenter(const glm::vec3 center){_center = center;}
    void setRadius(float radius){_radius = radius;}
    void rotate(float h_rotation, float v_rotation);

public slots:
    void rotate(int h_rotation, int v_rotation);
};
