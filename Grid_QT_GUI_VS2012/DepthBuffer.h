#pragma once

#include "GL\glew.h"

class DepthBuffer
{
protected:
    int _width;
    int _height;
    GLuint _id;

public:
    DepthBuffer(int width, int height);
    virtual ~DepthBuffer();
    GLuint id() const;
};