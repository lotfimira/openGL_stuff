#include "DepthBuffer.h"
#include "GlUtils.h"

DepthBuffer::DepthBuffer(int width, int height) : 
    _id(0)
{
    CLEAR_GL_ERRORS

    GLuint id;
    glGenRenderbuffers(1, &id);
    glBindRenderbuffer(GL_RENDERBUFFER, id);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    _id = id;
    _width = width;
    _height = height;

    CHECK_GL_ERRORS
}

DepthBuffer::~DepthBuffer()
{
    CLEAR_GL_ERRORS

    GLuint id = _id;
    if(glIsRenderbuffer(id))
        glDeleteRenderbuffers(1, &id);

    CHECK_GL_ERRORS
}

GLuint DepthBuffer::id() const
{
    return _id;
}