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
typedef std::shared_ptr<StreamTexture2D> StreamTexture2DPtr;

StreamArrayBufferPtr createStreamArrayBuffer(const QVector<glm::vec3> &);

StaticArrayBufferPtr createStaticArrayBuffer(const QVector<glm::vec4> &);
StaticArrayBufferPtr createStaticArrayBuffer(const QVector<glm::vec3> &);
StaticArrayBufferPtr createStaticArrayBuffer(const QVector<glm::vec2> &);

DepthBufferPtr createDepthBuffer(int width, int height);

Texture2DPtr createTexture(int width, int height, 
                           Texture2D::Type t = Texture2D::UByte);
Texture2DPtr createTexture(const QString & filename);
Texture2DPtr createTexture(int width, int height, 
                           const QVector<glm::u8vec4> &);

StreamTexture2DPtr createStreamTexture(int width, int height, 
                                       const QVector<glm::vec3> &);