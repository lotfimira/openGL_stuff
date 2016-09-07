#include "Mesh.h"
#include "GlUtils.h"
#include <QImage>
#include <QGLWidget>

GroundPlaneAnisotropic::GroundPlaneAnisotropic()
{
    _texture2D.load("E:\\lena_color.gif");
}

GroundPlaneAnisotropic::~GroundPlaneAnisotropic()
{

}

void GroundPlaneAnisotropic::draw()
{
    CLEAR_GL_ERRORS

    // no lighting
    glDisable(GL_LIGHTING);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _texture2D.id());

    CHECK_GL_ERRORS

    // white
    glColor4f(1, 1, 1, 1);

    // quad facing the camera
    int s = 100;
    int y = 0;
    glBegin(GL_QUADS);

    glTexCoord2f(0,0);
    glVertex3f(s, y, s);

    glTexCoord2f(0,1);
    glVertex3f(s, y, -s);

    glTexCoord2f(1,1);
    glVertex3f(-s, y, -s);

    glTexCoord2f(1,0);
    glVertex3f(-s, y, s);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    CHECK_GL_ERRORS
}