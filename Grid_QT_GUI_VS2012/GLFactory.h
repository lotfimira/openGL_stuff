#pragma once

#include "Buffer.h"
#include <glm/glm.hpp>
#include <QVector>

//-----------------------------------------------------------------------------
class GLFactory
{
public:
    static StreamArrayBufferPtr createStreamArrayBuffer(const QVector<glm::vec3> &);

    static StaticArrayBufferPtr createStaticArrayBuffer(const QVector<glm::vec4> &);
    static StaticArrayBufferPtr createStaticArrayBuffer(const QVector<glm::vec3> &);
    static StaticArrayBufferPtr createStaticArrayBuffer(const QVector<glm::vec2> &);
};