#pragma once

#include "Buffer.h"
#include "DepthBuffer.h"
#include "Texture.h"
#include "RenderTarget.h"
#include <glm/glm.hpp>
#include <QVector>

//-----------------------------------------------------------------------------
typedef std::shared_ptr<StaticArrayBuffer> StaticArrayBufferPtr;
typedef std::shared_ptr<StreamArrayBuffer> StreamArrayBufferPtr;
typedef std::shared_ptr<ArrayBuffer> ArrayBufferPtr;
typedef std::shared_ptr<DepthBuffer> DepthBufferPtr;
typedef std::shared_ptr<Texture2D> Texture2DPtr;

StreamArrayBufferPtr createStreamArrayBuffer(const QVector<glm::vec3> &);

StaticArrayBufferPtr createStaticArrayBuffer(const QVector<glm::vec4> &);
StaticArrayBufferPtr createStaticArrayBuffer(const QVector<glm::vec3> &);
StaticArrayBufferPtr createStaticArrayBuffer(const QVector<glm::vec2> &);

DepthBufferPtr createDepthBuffer(int width, int height);

Texture2DPtr createTexture(int width, int height, 
                           Texture2D::Type t = Texture2D::UByte);
Texture2DPtr createTexture(const QString & filename);