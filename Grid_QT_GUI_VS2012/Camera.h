#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

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
    Camera() : _pos(glm::vec3(0,0,-1)),
               _look_at(glm::vec3(0,0,0)), 
               _up(glm::vec3(0,1,0)) {}
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
    OrbitCamera(): _radius(0), _angle_h(0), _angle_v(0) {}

    void setCenter(const glm::vec3 center)
    {
        glm::vec3 new_pos = _pos + (center - _center);
        _center = center;

        LookAt(new_pos, _center, _up);
    }

    void setRadius(float radius)
    {
        glm::vec3 cam_unit_vector = glm::normalize(_pos - _center);
        glm::vec3 new_pos = cam_unit_vector * radius;
        _radius = radius;

        LookAt(new_pos, _center, _up);
    }

    void rotate(float h_rotation, float v_rotation);

    void printOrbitCamera();

public slots:
    void rotate(int h_rotation, int v_rotation);
};
