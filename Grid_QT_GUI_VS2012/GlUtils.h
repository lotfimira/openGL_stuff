#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <cstdio>

#define CLEAR_GL_ERRORS  \
{ \
    GLenum err = glGetError(); \
}

#define CHECK_GL_ERRORS  \
{ \
    GLenum err = glGetError(); \
    if (err) \
        printf( "GL error 0x%x \"%s\" at line %d in file %s\n", \
                err, gluErrorString(err), __LINE__, __FILE__); \
}

void renderArrow(const glm::vec3 & start, 
                 const glm::vec3 & stop,
                 const int size = 1.0f,
                 const glm::vec4 & color = glm::vec4(0,1,0,1));