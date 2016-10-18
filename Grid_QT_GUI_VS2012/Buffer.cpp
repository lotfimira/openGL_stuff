#include "Buffer.h"
#include "GlUtils.h"

//-----------------------------------------------------------------------------
BufferObject::BufferObject() : _id(0)
{
}

BufferObject::BufferObject(GLenum target, GLsizeiptr size, const GLvoid * data)
{
    CLEAR_GL_ERRORS

    GLuint buffer = 0;
    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, GL_STATIC_DRAW);
    glBindBuffer(target, 0);

    CHECK_GL_ERRORS

    _id = buffer;

    _auto_clean = std::make_shared<BufferAutoCleaner>(buffer);
}

BufferObject::~BufferObject()
{
}

GLuint BufferObject::id() const
{
    return _id;
}

bool BufferObject::isValid() const
{
    return glIsBuffer(_id);
}

//-----------------------------------------------------------------------------
ArrayBuffer::ArrayBuffer() : _nb_components_per_item(0), _nb_items(0), _type(0)
{
}

ArrayBuffer::ArrayBuffer(const QVector<glm::vec4> & array) :
    BufferObject(GL_ARRAY_BUFFER, array.size() * sizeof(glm::vec4), array.data())
{
    _nb_components_per_item = 4;
    _nb_items = array.size();
    _type = GL_FLOAT;
}

ArrayBuffer::ArrayBuffer(const QVector<glm::vec3> & array) :
    BufferObject(GL_ARRAY_BUFFER, array.size() * sizeof(glm::vec3), array.data())
{
    _nb_components_per_item = 3;
    _nb_items = array.size();
    _type = GL_FLOAT;
}

ArrayBuffer::ArrayBuffer(const QVector<glm::vec2> & array) :
    BufferObject(GL_ARRAY_BUFFER, array.size() * sizeof(glm::vec2), array.data())
{
    _nb_components_per_item = 2;
    _nb_items = array.size();
    _type = GL_FLOAT;
}

ArrayBuffer::~ArrayBuffer()
{
}

GLuint ArrayBuffer::nbItems() const
{
    return _nb_items;
}

GLuint ArrayBuffer::nbComponentsPerItem() const
{
    return _nb_components_per_item; 
}

GLenum ArrayBuffer::type() const
{
    return _type;
}

//-----------------------------------------------------------------------------
ElementArrayBuffer::ElementArrayBuffer() : _nb_elements(0)
{
}

ElementArrayBuffer::ElementArrayBuffer(const QVector<GLuint> & array) :
    BufferObject(GL_ELEMENT_ARRAY_BUFFER, array.size() * sizeof(GLuint), array.data())
{
    _nb_elements = array.size();
}

ElementArrayBuffer::~ElementArrayBuffer()
{
}

GLuint ElementArrayBuffer::nbElements() const
{
    return _nb_elements;
}
