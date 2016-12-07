#pragma once

#include "Mesh.h"
#include "StandardMaterial.h"
#include "GLFactory.h"

class WaterMesh : public Mesh
{
protected:
    Geometry _geometry;
    StandardMaterial _material;
    StreamArrayBufferPtr _pos_buffer;
    StreamArrayBufferPtr _normal_buffer;

    void initializeGeometry();
    void initializeMaterial();

public:
    WaterMesh();
    virtual ~WaterMesh();
    virtual void draw(const Camera &, const QVector<Light> & lights);
    virtual void animate();
};