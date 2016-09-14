#pragma once

#include "Texture.h"
#include <QString>

class Mesh
{
protected:
    GLuint createBuffer(GLenum target, GLsizeiptr size, const GLvoid * data);
    GLuint createArrayBuffer(GLsizeiptr size, const GLvoid * data);
    GLuint createElementArrayBuffer(GLsizeiptr size, const GLvoid * data);
    void deleteBuffer(GLuint & buffer);

public:
    virtual void draw() = 0;
};

class GroundPlaneAnisotropic : public Mesh
{
private:
    Texture2D _texture2D;

public:
    GroundPlaneAnisotropic();
    ~GroundPlaneAnisotropic();
    void draw();
};

class GridAnisotropic : public Mesh
{
private:
    Texture2D _texture2D;
    GLuint _pos_buffer;
    GLuint _index_buffer; // indexed geometry
    GLuint _color_buffer;
    GLuint _tex_coord_buffer;
    int _vert_count;

public:
    GridAnisotropic();
    ~GridAnisotropic();
    void draw();
};
