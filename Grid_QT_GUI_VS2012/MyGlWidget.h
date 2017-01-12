#pragma once

#include "Camera.h"
#include "Input.h"
#include "MeshList.h"
#include "Light.h"
#include "GLFactory.h"

#include <QGLWidget>
#include <QMouseEvent>
#include <QTimer>

//-----------------------------------------------------------------------------
class MyGlWidget : public QGLWidget
{
Q_OBJECT

private:
    OrbitCamera _camera;
    QVector<Light> _lights; // TODO: THIS SHOULD NOT BE HERE
    Input _input;
    QTimer _timer_refresh;
    bool _valid;
    DWORD _last_frame_time;
    bool _paused;
    //RenderTargetPtr _debug_render_target;

public:
    MyGlWidget(const QGLFormat & gl_format, QWidget *parent);
    virtual ~MyGlWidget();

protected:
    void initializeGL();
    void initRenderTargets(int width, int height);
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
    // THIS SHOULD NOT BE HERE
    void animateMeshes();
    void drawLights();
    void drawHud();
    void drawAxis();

protected slots:
    void onCameraChanged();
    void onRefreshTimout();
};