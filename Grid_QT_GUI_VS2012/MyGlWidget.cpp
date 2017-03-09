#include "MyGlWidget.h"
#include "WaterMesh.h" // SHOULD NOT BE HERE
#include "GlUtils.h"

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

    _paused = false;
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
    _camera.ViewPort(0, 0, w, h);
    
    _camera.Perspective(M_PI / 4.0f,         // fov 45 degrees
                        (float)w / (float)h, // aspect ratio
                        0.1f,     // near
                        1000.0f); // far
    /*
    float right  = w / 2;
    float left   = -right;
    float top    = h / 2;
    float bottom = -top;
    _camera.Ortho(left, right, bottom, top, -110.0f, 110.0f);*/

    initRenderTargets(w, h);
}

void MyGlWidget::initRenderTargets(int width, int height)
{
    // create render target for debugging shaders
    //_debug_render_target = createvec4FragmentTarget(width, height, 4);
}

void MyGlWidget::drawLights()
{
    for(int i = 0; i < _lights.size(); ++i)
    {
        Light & light = _lights[i];
        glm::vec3 origin = -light.direction() * 10.0f;
        renderArrow(origin, glm::vec3(0,0,0), 5.0);

        QString name = "Light " + QString::number(i);
        glm::vec2 screen_pos = _camera.worldToScreenPos(origin);
        renderText(screen_pos.x + 10, this->height() - screen_pos.y, name);
    }
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

    drawAxis();

    drawHud();

    // view light direction
    drawLights();

    // schedule next render
    if(!_paused)
        _timer_refresh.start();
}

void MyGlWidget::onRefreshTimout()
{
    animateMeshes();
    updateGL();
}

void MyGlWidget::drawHud()
{
    const int LINE_SPACE = 20;
    int x = 10;
    int y = LINE_SPACE;

    // compute fps
    DWORD now = GetTickCount();
    double fps = 1000.0 / double(now - _last_frame_time);
    _last_frame_time = now;
    glColor4f(1,1,1,1);
    renderText(x, y, QString::number(fps, 'f', 0) + " FPS");
    y += LINE_SPACE;

    // show camera pos
    glm::vec3 camera_pos = glm::normalize(_camera.pos());
    QString cam_pos = QString::number(camera_pos.x, 'f', 1) + " " +
                      QString::number(camera_pos.y, 'f', 1) + " " +
                      QString::number(camera_pos.z, 'f', 1);
    renderText(x, y, cam_pos);
    y += LINE_SPACE;

    if(_paused)
    {
        renderText(x, y, "Paused");
        y += LINE_SPACE;
    }

    DWORD ticks = GetTickCount();
    float time = (float)ticks / 1000.0f;
    renderText(x, y, QString("t = ") + QString::number(time));
    y += LINE_SPACE;
}

void MyGlWidget::drawAxis()
{
    float axis_size = 10;
    glLineWidth(1.0f);

    glColor4f(1,0,0,1);
    glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(axis_size,0,0);
    glEnd();

    glColor4f(0,1,0,1);
    glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(0,axis_size,0);
    glEnd();

    glColor4f(0,0,1,1);
    glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(0,0,axis_size);
    glEnd();
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
    if(event->key() == Qt::Key_P)
    {
        _paused = !_paused;
        if(!_paused)
            _timer_refresh.start();
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