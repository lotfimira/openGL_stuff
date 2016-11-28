#pragma once

#include <GL/glew.h>
#include <QVector>
#include <glm/glm.hpp>
#include "SelfCleaned.h"

//-----------------------------------------------------------------------------
class BufferObject : public SelfCleaned
{
protected:
    GLuint _id;

protected:
    BufferObject();
    BufferObject(GLenum target, 
                 GLsizeiptr size, 
                 const GLvoid * data, 
                 GLenum usage);
    virtual ~BufferObject();
    virtual void clean();

public:
    GLuint id() const;
    bool isValid() const;
};

//-----------------------------------------------------------------------------
class ArrayBuffer : public BufferObject
{
protected:
    GLuint _nb_components_per_item; // 1, 2, 3 or 4
    GLuint _nb_items;
    GLenum _type;

public:
    ArrayBuffer();
    ArrayBuffer(const QVector<glm::vec4> & array, GLenum usage);
    ArrayBuffer(const QVector<glm::vec3> & array, GLenum usage);
    ArrayBuffer(const QVector<glm::vec2> & array, GLenum usage);
    virtual ~ArrayBuffer();
    GLuint nbItems() const;
    GLuint nbComponentsPerItem() const;
    GLenum type() const;
};

//-----------------------------------------------------------------------------
class StaticArrayBuffer : public ArrayBuffer
{
public:
    StaticArrayBuffer();
    StaticArrayBuffer(const QVector<glm::vec4> & array);
    StaticArrayBuffer(const QVector<glm::vec3> & array);
    StaticArrayBuffer(const QVector<glm::vec2> & array);
    virtual ~StaticArrayBuffer();
};

//-----------------------------------------------------------------------------
class StreamArrayBuffer : public ArrayBuffer
{
public:
    StreamArrayBuffer();
    StreamArrayBuffer(const QVector<glm::vec4> & array);
    StreamArrayBuffer(const QVector<glm::vec3> & array);
    StreamArrayBuffer(const QVector<glm::vec2> & array);
    virtual ~StreamArrayBuffer();
    void update(const QVector<glm::vec4> & array);
    void update(const QVector<glm::vec3> & array);
    void update(const QVector<glm::vec2> & array);
};

//-----------------------------------------------------------------------------
class ElementArrayBuffer : public BufferObject
{
protected:
    GLuint _nb_elements;

public:
    ElementArrayBuffer();
    ElementArrayBuffer(const QVector<glm::uvec3> & array);
    ~ElementArrayBuffer();

    GLuint nbElements() const;
};

typedef std::shared_ptr<StaticArrayBuffer> StaticArrayBufferPtr;
typedef std::shared_ptr<StreamArrayBuffer> StreamArrayBufferPtr;
typedef std::shared_ptr<ArrayBuffer> ArrayBufferPtr;