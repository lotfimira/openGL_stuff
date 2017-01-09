#include "GLFactory.h"

//-----------------------------------------------------------------------------
StreamArrayBufferPtr createStreamArrayBuffer(const QVector<glm::vec3> & data)
{
    StreamArrayBufferPtr ptr = std::make_shared<StreamArrayBuffer>(data);
    return ptr;
}

StaticArrayBufferPtr createStaticArrayBuffer(const QVector<glm::vec4> & data)
{
    StaticArrayBufferPtr ptr = std::make_shared<StaticArrayBuffer>(data);
    return ptr;
}

StaticArrayBufferPtr createStaticArrayBuffer(const QVector<glm::vec3> & data)
{
    StaticArrayBufferPtr ptr = std::make_shared<StaticArrayBuffer>(data);
    return ptr;
}

StaticArrayBufferPtr createStaticArrayBuffer(const QVector<glm::vec2> & data)
{
    StaticArrayBufferPtr ptr = std::make_shared<StaticArrayBuffer>(data);
    return ptr;
}

DepthBufferPtr createDepthBuffer(int width, int height)
{
    return std::make_shared<DepthBuffer>(width, height);
}

Texture2DPtr createTexture(int width, int height, Texture2D::Type type)
{
    return std::make_shared<Texture2D>(width, height, type);
}

Texture2DPtr createTexture(const QString & filename)
{
    return std::make_shared<Texture2D>(filename);
}

StreamTexture2DPtr createStreamTexture(int width, int height, 
                                    const QVector<glm::vec3> & data)
{
    return std::make_shared<StreamTexture2D>(width, height, data);
}