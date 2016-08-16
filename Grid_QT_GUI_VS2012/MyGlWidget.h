#pragma once

#include <QGLWidget>
#include <QMouseEvent>
#include "Camera.h"
#include "Input.h"

class MyGlWidget : public QGLWidget
{
private:
    OrbitCamera _camera;
    Input _input;

public:
    MyGlWidget(QWidget *parent);
    virtual ~MyGlWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
};