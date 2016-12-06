#pragma once

#include "GLFactory.h"

class DepthBuffer
{
protected:
    int _width;
    int _height;
    GLuint _id;

public:
    DepthBuffer(int width, int height);
    virtual ~DepthBuffer();
};