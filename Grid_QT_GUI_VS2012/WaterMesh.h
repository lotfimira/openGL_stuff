#pragma once

#include "Mesh.h"
#include "StandardMaterial.h"
#include "GLFactory.h"

//-----------------------------------------------------------------------------
struct SineWave
{
    float amplitude;
    glm::vec2 direction;
    float omega; // angular speed (rad / terrain unit)
    float phase;

    SineWave() : amplitude(1), direction(1,0), omega(1), phase(0) {}
    float calc(float x, float y, float t) const;
};

class WaterMesh : public Mesh
{
protected:
    Geometry _geometry;
    StandardMaterial _material;
    StreamArrayBufferPtr _pos_buffer;
    StreamArrayBufferPtr _normal_buffer;
    QVector<SineWave> _waves;

    void initializeGeometry();
    void initializeMaterial();
    void computeShape(QVector<glm::vec3> & pos, 
                      QVector<glm::vec3> & normals, 
                      QVector<glm::uvec3> & triangles);

public:
    WaterMesh();
    virtual ~WaterMesh();
    virtual void draw(const Camera &, const QVector<Light> & lights);
    virtual void animate();
};