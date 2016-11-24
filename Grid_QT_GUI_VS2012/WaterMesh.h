#pragma once

#include "Mesh.h"
#include "StandardMaterial.h"

class WaterMesh : public Mesh
{
protected:
    Geometry _geometry;
    StandardMaterial _material;
    StreamArrayBuffer _pos_buffer;
    StreamArrayBuffer _normal_buffer;

    void initializeGeometry();
    void initializeMaterial();

public:
    WaterMesh();
    virtual ~WaterMesh();
    virtual void draw(const Camera &);
    virtual void animate();
};