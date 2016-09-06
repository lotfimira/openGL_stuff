#include "Mesh.h"
#include <QImage>
#include <QGLWidget>

/*
Texture Mesh::loadTexture(const QString & filename)
{
    Texture texture;

    glEnable(GL_TEXTURE_2D); // Enable texturing

    glGenTextures(1, &texture.id); // Obtain an id for the texture
    glBindTexture(GL_TEXTURE_2D, texture.id); // Set as the current texture

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    QImage im(filename);
    QImage tex = QGLWidget::convertToGLFormat(im);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.width(), tex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glDisable(GL_TEXTURE_2D);

    return texture;
}*/

GroundPlaneAnisotropic::GroundPlaneAnisotropic()
{
    _texture2D.load("E:\\mei.png");
}

GroundPlaneAnisotropic::~GroundPlaneAnisotropic()
{

}


void GroundPlaneAnisotropic::draw()
{
    // no lighting
    glDisable(GL_LIGHTING);

    glEnable(GL_TEXTURE_2D);

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

    glDisable(GL_TEXTURE_2D);
}