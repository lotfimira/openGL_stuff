#include "GlUtils.h"

//-----------------------------------------------------------------------------
void renderArrow(const glm::vec3 & start, 
                 const glm::vec3 & stop,
                 const int size,
                 const glm::vec4 & color)
{
    glColor4f(color.r, color.g, color.b, color.a);

    glLineWidth(size);

    glBegin(GL_LINES);
    glVertex3f(start.x, start.y, start.z);
    glVertex3f(stop.x, stop.y, stop.z);
    glEnd();

    glPointSize(size * 2.0f);

    glBegin(GL_POINTS);
    glVertex3f(stop.x, stop.y, stop.z);
    glEnd();
}