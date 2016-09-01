#include "MeshList.h"
#include <GL/glew.h>

void drawBlueQuad()
{
    // no lighting
    glDisable(GL_LIGHTING);

    // blue
    glColor4f(0, 0, 1, 1);

    // quad facing the camera
    int s = 1;
    int z = 0;
    glBegin(GL_QUADS);
    glVertex3f(-s, -s, z);
    glVertex3f(s, -s, z);
    glVertex3f(s, s, z);
    glVertex3f(-s, s, z);
    glEnd();
}

void drawGroundPlane()
{
    // no lighting
    glDisable(GL_LIGHTING);

    // white
    glColor4f(1, 1, 1, 1);

    // quad facing the camera
    int s = 100;
    int y = 0;
    glBegin(GL_QUADS);
    glVertex3f(s, y, s);
    glVertex3f(s, y, -s);
    glVertex3f(-s, y, -s);
    glVertex3f(-s, y, s);
    glEnd();
}

void MeshList::draw()
{
    drawGroundPlane();
}