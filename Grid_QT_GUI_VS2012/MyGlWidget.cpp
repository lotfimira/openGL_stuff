#include "MyGlWidget.h"

#define _USE_MATH_DEFINES
#include <math.h>

MyGlWidget::MyGlWidget(QWidget *parent) : QGLWidget(parent)
{
    QObject::connect(&_input,  SIGNAL(leftDrag(int, int)), 
                     &_camera, SLOT(rotate(int, int)));

    QObject::connect(&_input,  SIGNAL(midDrag(int, int)), 
                     &_camera, SLOT(translate(int, int)));

    QObject::connect(&_input,  SIGNAL(wheel(int)), 
                     &_camera, SLOT(zoom(int)));

    QObject::connect(&_camera, SIGNAL(changed()),
                     this,     SLOT(onCameraChanged()));

    setFocusPolicy(Qt::StrongFocus);
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

    _camera.setCenter(glm::vec3(0, 0, 0));
    _camera.setRadius(3.0f);
}

void MyGlWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);

    _camera.Perspective(M_PI / 4.0f,  // fov
                        (float)w / (float)h, // aspect ratio
                        0.1f,   // near
                        1000.0f); // far
}

void MyGlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _camera.GlLoadMatrices();

    _mesh_list.draw();

    _camera.printOrbitCamera();
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

void MyGlWidget::wheelEvent(QWheelEvent * event)
{
    _input.mouseWheelEvent(event);
}

void MyGlWidget::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Z)
    {
        centerOnScene();
    }
    else
    {
        QGLWidget::keyPressEvent(event);
    }
}

void MyGlWidget::onCameraChanged()
{
    updateGL();
}

void MyGlWidget::centerOnScene()
{
    _camera.setCenter(glm::vec3(0,0,0));
}