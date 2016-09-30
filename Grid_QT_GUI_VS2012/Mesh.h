#pragma once

#include "Texture.h"
#include "Camera.h"
#include "GLSLProgramObject.h"
#include "Buffer.h"
#include <QString>

class Mesh
{
public:
    virtual void draw(const Camera &) = 0;
    virtual ~Mesh(){}
};

class GroundPlaneAnisotropic : public Mesh
{
private:
    Texture2D _texture2D;

public:
    GroundPlaneAnisotropic();
    ~GroundPlaneAnisotropic();
    void draw(const Camera &);
};

class GridAnisotropic : public Mesh
{
protected:
    Texture2D _texture2D;
    ArrayBuffer _pos_buffer;
    ArrayBuffer _color_buffer;
    ArrayBuffer _tex_coord_buffer;
    ElementArrayBuffer _index_buffer; // indexed triangle geometry

public:
    GridAnisotropic();
    virtual ~GridAnisotropic();
    virtual void draw(const Camera &);
};

class ShadedGridAnisotropic : public GridAnisotropic
{
private:
    GLSLProgramObject _program;

public:
    ShadedGridAnisotropic();
    virtual ~ShadedGridAnisotropic();
    virtual void draw(const Camera &);
};
