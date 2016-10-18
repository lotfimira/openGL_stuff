#pragma once

#include <GL/glew.h>
#include <QVector>
#include <glm/glm.hpp>
#include <memory>

//-----------------------------------------------------------------------------
class BufferAutoCleaner
{
private:
    GLuint _id;

public:
    BufferAutoCleaner() : _id(0) {}
    BufferAutoCleaner(GLuint id) : _id(id) {}
    ~BufferAutoCleaner()
    {
        GLuint buffer_id = _id;
        if(glIsBuffer(buffer_id))
        {
            glDeleteBuffers(1, &buffer_id);
        }
    }
};

//-----------------------------------------------------------------------------
class BufferObject
{
protected:
    GLuint _id;
    std::shared_ptr<BufferAutoCleaner> _auto_clean;

protected:
    BufferObject();
    BufferObject(GLenum target, GLsizeiptr size, const GLvoid * data);
    virtual ~BufferObject();

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
    ArrayBuffer(const QVector<glm::vec4> & array);
    ArrayBuffer(const QVector<glm::vec3> & array);
    ArrayBuffer(const QVector<glm::vec2> & array);
    virtual ~ArrayBuffer();
    GLuint nbItems() const;
    GLuint nbComponentsPerItem() const;
    GLenum type() const;
};

//-----------------------------------------------------------------------------
class ElementArrayBuffer : public BufferObject
{
protected:
    GLuint _nb_elements;

public:
    ElementArrayBuffer();
    ElementArrayBuffer(const QVector<GLuint> & array);
    ~ElementArrayBuffer();

    GLuint nbElements() const;
};