#pragma once

#include "Texture.h"
#include "Camera.h"
#include "GLSLProgramObject.h"
#include "Buffer.h"
#include "Geometry.h"
#include "Material.h"
#include "Light.h"
#include "GridMaterial.h"
#include <QString>

//-----------------------------------------------------------------------------
class Mesh
{
protected:
    void drawTriangles(const Geometry & geometry, 
                       Material & material, 
                       const Camera & camera,
                       const QVector<Light> & lights = QVector<Light>());

public:
    virtual void draw(const Camera &, const QVector<Light> & lights) = 0;
    virtual void animate() {};
    virtual ~Mesh(){}
};

//-----------------------------------------------------------------------------
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
    GridMaterial _material;

    void initializeGeometry();
    void initializeMaterial();

public:
    GridAnisotropic();
    virtual ~GridAnisotropic();
    virtual void draw(const Camera &);
};
