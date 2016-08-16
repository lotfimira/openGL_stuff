#include "MyGlWidget.h"

#define _USE_MATH_DEFINES
#include <math.h>

MyGlWidget::MyGlWidget(QWidget *parent) : QGLWidget(parent)
{
    QObject::connect(&_input,  SIGNAL(drag(int, int)), 
                     &_camera, SLOT(addRotation(int, int)));
}

MyGlWidget::~MyGlWidget()
{
}

void MyGlWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    _camera.LookAt(glm::vec3(0, 0, -3), // eye
                   glm::vec3(0, 0, 0),  // center
                   glm::vec3(0, 1, 0)); // up
}

void MyGlWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);

    _camera.Perspective(M_PI / 4.0f,  // fov
                        (float)w / (float)h, // aspect ratio
                        0.1f,   // near
                        10.0f); // far
}

void MyGlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _camera.GlLoadMatrices();

    // no lighting
    glDisable(GL_LIGHTING);

    // blue
    glColor4f(0, 0, 1, 1);

    // quad facing the camera
    int s = 1;
    int z = 1;
    glBegin(GL_QUADS);
    glVertex3f(-s, -s, z);
    glVertex3f(s, -s, z);
    glVertex3f(s, s, z);
    glVertex3f(-s, s, z);
    glEnd();
}

void MyGlWidget::mousePressEvent(QMouseEvent * event)
{
    _input.mousePressEvent(event);
}

void MyGlWidget::mouseReleaseEvent(QMouseEvent * event)
{
    _input.mouseReleaseEvent(event);
}

void MyGlWidget::mouseMoveEvent(QMouseEvent * event)
{
    _input.mouseMoveEvent(event);
}
