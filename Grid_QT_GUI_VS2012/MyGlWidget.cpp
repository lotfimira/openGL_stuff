#include "MyGlWidget.h"

MyGlWidget::MyGlWidget()
{
}

MyGlWidget::~MyGlWidget()
{
}

void MyGlWidget::initializeGL()
{
    _camera.LookAt(glm::vec3(0, 0, -3), // eye
                   glm::vec3(0, 0, 0),  // center
                   glm::vec3(0, 1, 0)); // up
}

void MyGlWidget::resizeGL(int w, int h)
{
    _camera.Perspective(45.0f,  // fov
                        (float)w / (float)h, // aspect ratio
                        0.1f,   // near
                        10.0f); // far

    //_camera.Frustum(-2, +2, -2, +2, 0.1f, 10.0f);
}

void MyGlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    _camera.GlLoadMatrices();

    // no lighting
    glDisable(GL_LIGHTING);

    // blue
    glColor4f(0, 0, 1, 1);

    // quad facing the camera
    glBegin(GL_QUADS);
    glVertex3f(-1, -1, 0);
    glVertex3f(1, -1, 0);
    glVertex3f(1, 1, 0);
    glVertex3f(-1, 1, 0);
    glEnd();
}
