#pragma once

#include <QtOpenGL/QGLWidget>
#include "Camera.h"

class MyGlWidget : public QGLWidget
{
private:
    Camera _camera;

public:
    MyGlWidget();
    virtual ~MyGlWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};