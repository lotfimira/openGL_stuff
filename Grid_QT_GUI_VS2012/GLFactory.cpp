#include "GLFactory.h"

//-----------------------------------------------------------------------------
StreamArrayBufferPtr GLFactory::createStreamArrayBuffer(const QVector<glm::vec3> & data)
{
    StreamArrayBufferPtr ptr = std::make_shared<StreamArrayBuffer>(data);
    return ptr;
}

StaticArrayBufferPtr GLFactory::createStaticArrayBuffer(const QVector<glm::vec4> & data)
{
    StaticArrayBufferPtr ptr = std::make_shared<StaticArrayBuffer>(data);
    return ptr;
}

StaticArrayBufferPtr GLFactory::createStaticArrayBuffer(const QVector<glm::vec3> & data)
{
    StaticArrayBufferPtr ptr = std::make_shared<StaticArrayBuffer>(data);
    return ptr;
}

StaticArrayBufferPtr GLFactory::createStaticArrayBuffer(const QVector<glm::vec2> & data)
{
    StaticArrayBufferPtr ptr = std::make_shared<StaticArrayBuffer>(data);
    return ptr;
}
