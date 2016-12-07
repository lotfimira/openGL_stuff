#pragma once

#include "GLFactory.h"
#include "SelfCleaned.h"
#include "DepthBuffer.h"
#include "Texture.h"

class RenderTarget
{
protected:
    //FrameBuffer _frame_buffer;
    //DepthBufferPtr _depth_buffer;
    Texture2D _texture;

public:
    RenderTarget(int width, int height);
    virtual ~RenderTarget();
};