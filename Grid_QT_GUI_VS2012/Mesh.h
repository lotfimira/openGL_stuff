#pragma once

#include "Texture.h"
#include "Camera.h"
#include "GLSLProgramObject.h"
#include "Buffer.h"
#include <QString>

//-----------------------------------------------------------------------------
class Mesh
{
protected:
    void drawTriangles(const Geometry & geometry, 
                       Material & material, 
                       const Camera & camera);

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

//-----------------------------------------------------------------------------
class GridAnisotropic : public Mesh
{
protected:
    Geometry _geometry;
    Material _material;

    void initializeGeometry();
    void initializeMaterial();

public:
    GridAnisotropic();
    virtual ~GridAnisotropic();
    virtual void draw(const Camera &);
};
