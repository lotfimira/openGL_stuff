#include "MeshList.h"
#include <GL/glew.h>

void MeshList::draw()
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