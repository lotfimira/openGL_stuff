#include "Camera.h"
#include <GL/glew.h>

#define _USE_MATH_DEFINES
#include <math.h>

#define GLM_FORCE_RADIANS 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

void Camera::LookAt(glm::vec3 eye, glm::vec3 lookat, glm::vec3 up)
{
    _view_mat = glm::lookAt(eye, lookat, up);
    _normal_mat = glm::transpose(glm::inverse(glm::mat3(_view_mat)));

    _look_at = lookat;
    _pos = eye;
    _up = up;
}

void Camera::Perspective(float fovy_rad, float aspect_ratio, float near, float far)
{
    _proj_mat = glm::perspective(fovy_rad, aspect_ratio, near, far);
}

void Camera::Frustum(float left, float right, float bottom, float top, float near, float far)
{
    _proj_mat = glm::frustum(left, right, bottom, top, near, far);
}

void Camera::GlLoadMatrices()
{
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(_proj_mat));

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(_view_mat));
}

void Camera::ViewPort(int left, int bottom, int width, int height)
{
    _view_port = glm::ivec4(left, bottom, width, height);
    glViewport(left, bottom, width, height); // TODO is this the proper place?
}

glm::mat4 Camera::mvpMat() const
{
    // TODO: this costs a multiplication for every mesh that uses it
    return _proj_mat *_view_mat;
}

glm::mat4 Camera::viewMat() const
{
    return _view_mat;
}

glm::mat3 Camera::normalMat() const
{
    return _normal_mat;
}

glm::vec3 Camera::pos() const
{
    return _pos;
}

glm::vec2 Camera::worldToScreenPos(const glm::vec3 & world_pos) const
{
   glm::vec3 screen_pos = glm::project(world_pos, 
                                       _view_mat, 
                                       _proj_mat, 
                                       _view_port);

   return glm::vec2(screen_pos);
}

//-----------------------------------------------------------------------------
void OrbitCamera::rotate(int x, int y)
{
    float h_rad = ((float)x) * 2.0f * M_PI / 360.0f;
    float v_rad = ((float)y) * 2.0f * M_PI / 360.0f;

    rotate(h_rad, v_rad);
}

//-----------------------------------------------------------------------------
void OrbitCamera::translate(int x, int y)
{
    GLint vport[4];
    glGetIntegerv(GL_VIEWPORT, vport);

    glm::ivec4 viewport = glm::ivec4(vport[0], vport[1], vport[2], vport[3]);
    glm::vec3 center_screen = glm::project(_center, _view_mat, _proj_mat, viewport);

    center_screen.x -= x;
    center_screen.y += y;

    glm::vec3 center_world = glm::unProject(center_screen, _view_mat, _proj_mat, viewport);

    setCenter(center_world);
}

void printVector(const QString & name, const glm::vec3 & v)
{
    printf("%s [%.1f %.1f %.1f]\n", name.toStdString().c_str(),
        v.x, v.y, v.z);
}

void OrbitCamera::printOrbitCamera()
{
    printf("Orbit Camera\n");
    printVector("center", _center);
    printVector("look at", _look_at);
    printVector("pos", _pos);
    printVector("up", _up);
    printf("radius %f\n", _radius);
    printf("angle h %.1f\n", _angle_h);
    printf("angle v %.1f\n", _angle_v);
    printf("\n");
}

// normalize angle [0 , 2 PI]
void normalizeAngle(float & angle)
{
    angle = fmod(angle, 2 * M_PI);

    if(angle < 0)
        angle += 2 * M_PI;
}

//-----------------------------------------------------------------------------
void OrbitCamera::rotate(float h_rad, float v_rad)
{
    // add rotation
    _angle_h -= h_rad;
    normalizeAngle(_angle_h);

    _angle_v += v_rad;
    normalizeAngle(_angle_v);

    // cam vector from center to eye pos
    glm::vec3 cam_vector = _center;
    cam_vector.z -= _radius;

    // up vector
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    // vertical rotation
    const glm::vec3 X_AXIS = glm::vec3(1.0f, 0.0f, 0.0f);
    cam_vector = glm::rotate(cam_vector, _angle_v, X_AXIS);
    up = glm::rotate(up, _angle_v, X_AXIS);

    // horizontal rotation
    const glm::vec3 Y_AXIS = glm::vec3(0.0f, 1.0f, 0.0f);
    cam_vector = glm::rotate(cam_vector, _angle_h, Y_AXIS);
    up = glm::rotate(up, _angle_h, Y_AXIS);

    glm::vec3 eye = _center + cam_vector;
    LookAt(eye, _center, up);

    emit changed();
}

//-----------------------------------------------------------------------------
void OrbitCamera::zoom(int delta)
{
    float step = (((float)delta) / 8.0f) / 15.0f;
    step = -step;

    float radius = _radius + (_radius * 10.0f / 100.0f) * step;
    setRadius(radius);
}