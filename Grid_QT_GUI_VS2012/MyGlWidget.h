#pragma once

#include "Camera.h"
#include "Input.h"
#include "MeshList.h"

#include <QGLWidget>
#include <QMouseEvent>
#include <QTimer>

class MyGlWidget : public QGLWidget
{
Q_OBJECT

private:
    OrbitCamera _camera;
    Input _input;

public:
    MyGlWidget(const QGLFormat & gl_format, QWidget *parent);
    virtual ~MyGlWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void wheelEvent(QWheelEvent * event);
    void keyPressEvent(QKeyEvent * event);
    void centerOnScene();

    // THIS SHOULD NOT BE HERE
    void prepareScene();

protected slots:
    void onCameraChanged();
};