#include "Camera.h"
//#include "Camera.moc"
#include <GL/glew.h>
#define GLM_FORCE_RADIANS 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#define UP glm::vec3(0,0,1)

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

void OrbitCamera::h_rotate(float rad)
{
    glm::vec3 cam_reverse_vector = _pos - _look_at;
    cam_reverse_vector = glm::rotate(cam_reverse_vector, rad, UP);
    _pos = _look_at + cam_reverse_vector;

    _view_mat = glm::lookAt(_pos, _look_at, _up);
}

void OrbitCamera::v_rotate(float rad)
{
    glm::vec3 cam_reverse_vector = _pos - _look_at;
    glm::vec3 rotation_axis = glm::vec3( -cam_reverse_vector.y, cam_reverse_vector.x, 0);
    cam_reverse_vector = glm::rotate(cam_reverse_vector, rad, rotation_axis);
    _pos = _look_at + cam_reverse_vector;

    _view_mat = glm::lookAt(_pos, _look_at, _up);
}
