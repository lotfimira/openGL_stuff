#pragma once

#include "Mesh.h"
#include "StandardMaterial.h"

class WaterMesh : public Mesh
{
protected:
    Geometry _geometry;
    StandardMaterial _material;

    void initializeGeometry();
    void initializeMaterial();

public:
    WaterMesh();
    virtual ~WaterMesh();
    virtual void draw(const Camera &);
};