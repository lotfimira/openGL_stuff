#include "Buffer.h"
#include "GlUtils.h"
#include "MyException.h"

//-----------------------------------------------------------------------------
BufferObject::BufferObject() : _id(0)
{
}

BufferObject::BufferObject(GLenum target, 
                           GLsizeiptr size, 
                           const GLvoid * data,
                           GLenum usage)
{
    CLEAR_GL_ERRORS

    GLuint buffer = 0;
    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, usage);
    glBindBuffer(target, 0);

    CHECK_GL_ERRORS

    _id = buffer;
}

BufferObject::~BufferObject()
{
    // checks reference counter, if last then call clean()
    autoClean();
}

GLuint BufferObject::id() const
{
    return _id;
}

bool BufferObject::isValid() const
{
    return glIsBuffer(_id);
}

void BufferObject::clean()
{
    CLEAR_GL_ERRORS

    GLuint buffer = _id;
    if(glIsBuffer(buffer))
    {
        glDeleteBuffers(1, & buffer);
        _id = 0;
    }

    CHECK_GL_ERRORS
}

//-----------------------------------------------------------------------------
ArrayBuffer::ArrayBuffer() : _nb_components_per_item(0), _nb_items(0), _type(0)
{
}

ArrayBuffer::ArrayBuffer(const QVector<glm::vec4> & array, GLenum usage) :
    BufferObject(GL_ARRAY_BUFFER, 
                 array.size() * sizeof(glm::vec4), 
                 array.data(),
                 usage)
{
    _nb_components_per_item = 4;
    _nb_items = array.size();
    _type = GL_FLOAT;
}

ArrayBuffer::ArrayBuffer(const QVector<glm::vec3> & array, GLenum usage) :
    BufferObject(GL_ARRAY_BUFFER, 
                 array.size() * sizeof(glm::vec3), 
                 array.data(),
                 usage)
{
    _nb_components_per_item = 3;
    _nb_items = array.size();
    _type = GL_FLOAT;
}

ArrayBuffer::ArrayBuffer(const QVector<glm::vec2> & array, GLenum usage) :
    BufferObject(GL_ARRAY_BUFFER, 
                 array.size() * sizeof(glm::vec2), 
                 array.data(),
                 usage)
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

ElementArrayBuffer::ElementArrayBuffer(const QVector<glm::uvec3> & array) :
    BufferObject(GL_ELEMENT_ARRAY_BUFFER, 
                 array.size() * sizeof(glm::uvec3), 
                 array.data(),
                 GL_STATIC_DRAW)
{
    _nb_elements = array.size() * 3;
}

ElementArrayBuffer::~ElementArrayBuffer()
{
}

GLuint ElementArrayBuffer::nbElements() const
{
    return _nb_elements;
}

//-----------------------------------------------------------------------------
StaticArrayBuffer::StaticArrayBuffer()
{
}

StaticArrayBuffer::StaticArrayBuffer(const QVector<glm::vec4> & array)
    : ArrayBuffer(array, GL_STATIC_DRAW)
{
}

StaticArrayBuffer::StaticArrayBuffer(const QVector<glm::vec3> & array)
    : ArrayBuffer(array, GL_STATIC_DRAW)
{
}

StaticArrayBuffer::StaticArrayBuffer(const QVector<glm::vec2> & array)
    : ArrayBuffer(array, GL_STATIC_DRAW)
{
}

StaticArrayBuffer::~StaticArrayBuffer()
{
}

//-----------------------------------------------------------------------------
StreamArrayBuffer::StreamArrayBuffer()
{
}

StreamArrayBuffer::StreamArrayBuffer(const QVector<glm::vec4> & array)
    : ArrayBuffer(array, GL_STREAM_DRAW)
{
}

StreamArrayBuffer::StreamArrayBuffer(const QVector<glm::vec3> & array)
    : ArrayBuffer(array, GL_STREAM_DRAW)
{
}

StreamArrayBuffer::StreamArrayBuffer(const QVector<glm::vec2> & array)
    : ArrayBuffer(array, GL_STREAM_DRAW)
{
}

StreamArrayBuffer::~StreamArrayBuffer()
{
}

//-----------------------------------------------------------------------------
void StreamArrayBuffer::update(const QVector<glm::vec4> & array)
{
    if(!isValid())
        return;

    if(_nb_components_per_item != 4)
        throw new MyException("StreamArrayBuffer::update unmatch nb of items");

    if(_type != GL_FLOAT)
        throw new MyException("StreamArrayBuffer::update unmatch type");

    glBufferData(GL_ARRAY_BUFFER, 
                 sizeof(glm::vec4) * array.size(), 
                 array.data(), 
                 GL_STREAM_DRAW);
}

void StreamArrayBuffer::update(const QVector<glm::vec3> & array)
{
    if(!isValid())
        return;

    if(_nb_components_per_item != 3)
        throw new MyException("StreamArrayBuffer::update unmatch nb of items");

    if(_type != GL_FLOAT)
        throw new MyException("StreamArrayBuffer::update unmatch type");

    glBufferData(GL_ARRAY_BUFFER, 
                 sizeof(glm::vec3) * array.size(), 
                 array.data(), 
                 GL_STREAM_DRAW);
}

void StreamArrayBuffer::update(const QVector<glm::vec2> & array)
{
    if(!isValid())
        return;

    if(_nb_components_per_item != 2)
        throw new MyException("StreamArrayBuffer::update unmatch nb of items");

    if(_type != GL_FLOAT)
        throw new MyException("StreamArrayBuffer::update unmatch type");

    glBufferData(GL_ARRAY_BUFFER, 
                 sizeof(glm::vec2) * array.size(), 
                 array.data(), 
                 GL_STREAM_DRAW);
}
