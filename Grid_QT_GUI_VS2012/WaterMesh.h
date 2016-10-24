#pragma once

#include "Mesh.h"

class WaterMesh : public Mesh
{
protected:
    Geometry _geometry;
    Material _material;

    void initializeGeometry();
    void initializeMaterial();

public:
    WaterMesh();
    virtual ~WaterMesh();
    virtual void draw(const Camera &);
};