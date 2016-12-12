#include "MyGlWidget.h"
#include "WaterMesh.h" // SHOULD NOT BE HERE

#define _USE_MATH_DEFINES
#include <math.h>

MyGlWidget::MyGlWidget(const QGLFormat & format, QWidget *parent) : 
            QGLWidget(format, parent)
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

    _last_frame_time = GetTickCount();

    _timer_refresh.setInterval(1000 / 60);
    _timer_refresh.setSingleShot(true);
    QObject::connect(&_timer_refresh, SIGNAL(timeout()), this, SLOT(onRefreshTimout()));
}

MyGlWidget::~MyGlWidget()
{
    MeshList::instance()->clean();
}

void MyGlWidget::initializeGL()
{
    if (glewInit() != GLEW_OK)
    {
        printf("ERROR: failed to initialize GLEW\n");
        getchar();
        exit(1);
    }

    printf("Running on a %s\nfrom %s\nOpenGL version %s\n",
           (const char *)(glGetString(GL_RENDERER)),
           (const char *)(glGetString(GL_VENDOR)),
           (const char *)(glGetString(GL_VERSION)));

    // THIS SHOULD NOT BE HERE
    prepareScene();

    Light sun(glm::vec3(-1,-1,-1));
    _lights.push_back(sun);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_MULTISAMPLE);

    _camera.setCenter(glm::vec3(0, 0, 0));
    _camera.setRadius(3.0f);

    initRenderTargets(width(), height());
}

void MyGlWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);

    _camera.Perspective(M_PI / 4.0f,  // fov
                        (float)w / (float)h, // aspect ratio
                        0.1f,   // near
                        1000.0f); // far

    initRenderTargets(w, h);
}

void MyGlWidget::initRenderTargets(int width, int height)
{
    // create render target for debugging shaders
    //_debug_render_target = createvec4FragmentTarget(width, height, 4);
}

void MyGlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // render
    _camera.GlLoadMatrices();
    MeshList::instance()->draw(_camera, _lights);

    // debug render
    //_debug_render_target->bind();
    //MeshList::instance()->draw(_camera, _lights);
    //_debug_render_target->unbind();

    // compute fps
    DWORD now = GetTickCount();
    double fps = 1000.0 / double(now - _last_frame_time);
    _last_frame_time = now;
    renderText(10, 20, QString::number(fps, 'f', 0) + " FPS");

    // show camera pos
    QString cam_pos = QString::number(_camera.pos().x, 'f', 1) + " " +
                      QString::number(_camera.pos().y, 'f', 1) + " " +
                      QString::number(_camera.pos().z, 'f', 1);
    renderText(10, 40, cam_pos);

    // schedule next render
    _timer_refresh.start();
}

void MyGlWidget::onRefreshTimout()
{
    animateMeshes();
    updateGL();
}

//-----------------------------------------------------------------------------
void MyGlWidget::mousePressEvent(QMouseEvent * event)
{
    // the next instructions will use OpenGL so make
    // the windows openGL context current
    makeCurrent();

    _input.mousePressEvent(event);
}

void MyGlWidget::mouseReleaseEvent(QMouseEvent * event)
{
    // the next instructions will use OpenGL so make
    // the windows openGL context current
    makeCurrent();

    _input.mouseReleaseEvent(event);
}

void MyGlWidget::mouseMoveEvent(QMouseEvent * event)
{
    // the next instructions will use OpenGL so make
    // the windows openGL context current
    makeCurrent();

    _input.mouseMoveEvent(event);
}

void MyGlWidget::wheelEvent(QWheelEvent * event)
{
    // the next instructions will use OpenGL so make
    // the windows openGL context current
    makeCurrent();

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

// THIS SHOULD NOT BE HERE
void MyGlWidget::prepareScene()
{
    //GroundPlaneAnisotropic * groundPlaneAnisotropic = new GroundPlaneAnisotropic();
    //MeshList::instance()->addMesh(groundPlaneAnisotropic);

    //GridAnisotropic * grid_anisotropic = new GridAnisotropic();
    //MeshList::instance()->addMesh(grid_anisotropic);

    WaterMesh * water_mesh = new WaterMesh();
    MeshList::instance()->addMesh(water_mesh);
}

// THIS SHOULD NOT BE HERE
void MyGlWidget::animateMeshes()
{
    MeshList::instance()->animate();
}