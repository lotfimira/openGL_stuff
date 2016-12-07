#include "RenderTarget.h"

//-----------------------------------------------------------------------------
RenderTarget::RenderTarget(int width, int height)
{
    _texture = Texture2D(width, height);
    _texture.setFiltering(Texture2D::Nearest);

    //_depth_buffer = createDepthBuffer(width, height);

    //_frame_buffer = FrameBuffer(_texture, _depth_buffer);
}

RenderTarget::~RenderTarget()
{
}