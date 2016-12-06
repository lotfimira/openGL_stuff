#pragma once

#include "GLFactory.h"

class FrameBuffer
{
protected:
    GLuint _id;
    QVector<Texture2DPtr> _textures;
    DepthBufferPtr _depth_buffer;

public:
    FrameBuffer();
    virtual ~FrameBuffer();
    void setDepthBuffer(DepthBufferPtr depth_buffer);
    void addColorAttachment(Texture2DPtr texture);
    bool isValid() const;
};