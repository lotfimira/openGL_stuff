#pragma once

#include "Mesh.h"
#include "StandardMaterial.h"
#include "WireframeMaterial.h"
#include "NormalMaterial.h"
#include "NormalTextureMaterial.h"
#include "StreamTextureMaterial.h"
#include "TextureMaterial.h"
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
    WireframeMaterial _wireframe_material;
    NormalMaterial _normal_material;
    NormalTextureMaterial _normal_texture_material;
    StreamTextureMaterial _stream_texture_material;
    TextureMaterial _texture_material;
    StreamArrayBufferPtr _pos_buffer;
    QVector<SineWave> _waves;

    void initializeGeometry();
    void initializeMaterial();
    void computeShape(QVector<glm::vec3> & pos, 
                      QVector<glm::vec3> & normals, 
                      QVector<glm::vec2> & tex_coords,
                      QVector<glm::uvec3> & triangles);

public:
    WaterMesh();
    virtual ~WaterMesh();
    virtual void draw(const Camera &, const QVector<Light> & lights);
    virtual void WaterMesh::draw(const Camera & camera, 
                                 const QVector<Light> & lights, 
                                 Material & material);
    virtual void animate();
};