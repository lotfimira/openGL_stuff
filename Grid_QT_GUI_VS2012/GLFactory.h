#pragma once

#include "Buffer.h"
#include <glm/glm.hpp>
#include <QVector>

//-----------------------------------------------------------------------------
StreamArrayBufferPtr createStreamArrayBuffer(const QVector<glm::vec3> &);

StaticArrayBufferPtr createStaticArrayBuffer(const QVector<glm::vec4> &);
StaticArrayBufferPtr createStaticArrayBuffer(const QVector<glm::vec3> &);
StaticArrayBufferPtr createStaticArrayBuffer(const QVector<glm::vec2> &);
