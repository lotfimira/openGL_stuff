#pragma once

#include <GL/glew.h>
#include <cstdio>

#define CLEAR_GL_ERRORS  \
{ \
    GLenum err = glGetError(); \
}

#define CHECK_GL_ERRORS  \
{ \
    GLenum err = glGetError(); \
    if (err) \
        printf( "GL error 0x%x \"%s\" at line %d in file %s\n", err, gluErrorString(err), __LINE__, __FILE__); \
}
