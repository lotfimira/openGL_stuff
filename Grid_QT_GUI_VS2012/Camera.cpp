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

void OrbitCamera::rotate(int h_rotation, int v_rotation)
{
    float h_rad = ((float)h_rotation) * 2.0f * M_PI / 360.0f;
    float v_rad = ((float)v_rotation) * 2.0f * M_PI / 360.0f;

    rotate(h_rad, v_rad);
}

void OrbitCamera::rotate(float h_rad, float v_rad)
{
    // add rotation
    _angle_h += h_rad;
    _angle_h = fmod(_angle_h, 2 * M_PI); // normalize angle [0 , 2 PI]

    _angle_v += v_rad;
    _angle_v = fmod(_angle_v, 2 * M_PI);

    glm::vec3 cam_vector = _center;
    cam_vector.z -= _radius;

    // vertical rotation
    cam_vector = glm::rotate(cam_vector,
                             _angle_v,
                             glm::vec3(1.0f, 0.0f, 0.0f));

    // horizontal rotation
    const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
    cam_vector = glm::rotate(cam_vector,
                             _angle_h,
                             UP);

    LookAt(_center + cam_vector, _center, UP);

    emit changed();
}