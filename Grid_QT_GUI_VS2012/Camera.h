#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <QObject>

struct FrustumStruct
{
    float left;
    float right;
    float bottom;
    float top;
    float near;
    float far;
    FrustumStruct() : left(0), right(0), bottom(0), top(0), near(0), far(0) {}
    FrustumStruct(float fovy, float ar, float n, float f);
    FrustumStruct(float l, float r, float b, float t, float n, float f);
};

enum ProjectionType
{
    Perspective = 0,
    Ortho
};

class Camera : public QObject
{
Q_OBJECT

protected:
    glm::vec3 _pos;
    glm::vec3 _look_at;
    glm::vec3 _up;
    glm::ivec4 _view_port;

    glm::mat4 _view_mat;
    glm::mat4 _proj_mat;
    glm::mat3 _normal_mat;

    FrustumStruct _frustum;
    ProjectionType _projection_type;

public:
    Camera() : _pos(glm::vec3(0,0,1)),
               _look_at(glm::vec3(0,0,0)), 
               _up(glm::vec3(0,1,0)),
               _view_port(glm::ivec4(0, 0, 100, 100)),
               _projection_type(ProjectionType::Ortho) {}
    ~Camera() {};

    void LookAt(glm::vec3 eye, glm::vec3 lookat, glm::vec3 up);
    void Perspective(float fovy_rad, float aspect_ratio, float near, float far);
    void Frustum(float left, float right, float bottom, float top, float near, float far);
    void Ortho(float left, float right, float bottom, float top, float near, float far);
    void GlLoadMatrices();
    void ViewPort(int left, int bottom, int width, int height);

    glm::mat4 mvpMat() const;
    glm::mat4 viewMat() const;
    glm::mat3 normalMat() const;
    glm::vec3 pos() const;
    glm::vec2 worldToScreenPos(const glm::vec3 &) const;

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

        emit changed();
    }

    void setRadius(float radius)
    {
        glm::vec3 cam_unit_vector = glm::normalize(_pos - _center);
        glm::vec3 new_pos = _center + cam_unit_vector * radius;
        _radius = radius;

        LookAt(new_pos, _center, _up);

        emit changed();
    }

    void rotate(float h_rotation, float v_rotation);

    void printOrbitCamera();

public slots:
    void rotate(int x, int y);
    void translate(int x, int y);
    void zoom(int delta);
};
