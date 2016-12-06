#include "FrameBuffer.h"
#include "GlUtils.h"

//-----------------------------------------------------------------------------
FrameBuffer::FrameBuffer() :
    _id(0)
{
    CLEAR_GL_ERRORS

    GLuint id = 0;
    glGenFramebuffers(1, &id);

    _id = id;

    CHECK_GL_ERRORS
}

FrameBuffer::~FrameBuffer()
{
}

void FrameBuffer::setDepthBuffer(DepthBufferPtr depth_buffer)
{
    if(!isValid())
    {
        printf("FrameBuffer::setDepthBuffer invalid FrameBuffer\n");
        return;
    }

    CLEAR_GL_ERRORS

    GLuint id = _id;
    glBindFramebuffer(GL_FRAMEBUFFER, id);

    // attach depth buffer
    GLuint depth_buffer_id = 0;
    if(depth_buffer)
        depth_buffer_id = depth_buffer->id();

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, 
                              GL_DEPTH_ATTACHMENT, 
                              GL_RENDERBUFFER, 
                              depth_buffer_id);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    CHECK_GL_ERRORS

    _depth_buffer = depth_buffer;
}

void FrameBuffer::addColorAttachment(Texture2DPtr texture)
{
    if(!isValid())
    {
        printf("FrameBuffer::setDepthBuffer invalid FrameBuffer\n");
        return;
    }

        // attach texture
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

}

bool FrameBuffer::isValid() const
{
    GLuint id = _id;
    return glIsFramebuffer(id);
}