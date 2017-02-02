#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

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
    float wavelength;
    float phase;

    SineWave() : amplitude(1), wavelength(1), phase(0) {}
    virtual float calc(const glm::vec2 & pos) const = 0;
};

struct DirectionalWave : public SineWave
{
    glm::vec2 direction;
    DirectionalWave() : direction(1,0) {}
    float calc(const glm::vec2 & pos) const;
    static std::shared_ptr<DirectionalWave> create() { return std::make_shared<DirectionalWave>(); }
};

struct CircularWave : public SineWave
{
    glm::vec2 origin;
    CircularWave() : origin(0,0) {}
    float calc(const glm::vec2 & pos) const;
    static std::shared_ptr<CircularWave> create() { return std::make_shared<CircularWave>(); }
};

typedef std::shared_ptr<SineWave> SineWavePtr;
typedef std::shared_ptr<DirectionalWave> DirectionalWavePtr;
typedef std::shared_ptr<CircularWave> CircularWavePtr;

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
    QVector<SineWavePtr> _waves;

    void initializeGeometry();
    void initializeMaterial();
    void computeShape(QVector<glm::vec3> & pos, 
                      QVector<glm::vec3> & normals, 
                      QVector<glm::vec2> & tex_coords,
                      QVector<glm::uvec3> & triangles);
    QVector<glm::vec3> mapNormals(const QVector<glm::vec3> & normals);

public:
    WaterMesh();
    virtual ~WaterMesh();
    virtual void draw(const Camera &, const QVector<Light> & lights);
    virtual void WaterMesh::draw(const Camera & camera, 
                                 const QVector<Light> & lights, 
                                 Material & material);
    virtual void animate();
};