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
class SineWave
{
protected:
    float _amplitude;
    float _wavelength;
    float _phase;

public:
    SineWave() : _amplitude(1), _wavelength(1), _phase(0) {}
    virtual ~SineWave(){}
    virtual glm::vec3 calc(const glm::vec2 & pos,
                           const int count_waves = 1) const = 0;
    void setAmplitude(float amplitude) {_amplitude = amplitude;}
    void setWavelength(float wavelength) {_wavelength = wavelength;}
    void setPhase(float phase) {_phase = phase;}
};

class DirectionalWave : public SineWave
{
protected:
    glm::vec2 _direction;

public:
    DirectionalWave() : _direction(1,0) {}
    virtual ~DirectionalWave(){}
    virtual glm::vec3 calc(const glm::vec2 & pos,
                           const int count_waves = 1) const;
    void setDirection(const glm::vec2 & direction)
    {
        _direction = glm::normalize(direction);
    }
    static std::shared_ptr<DirectionalWave> create() { return std::make_shared<DirectionalWave>(); }
};

class CircularWave : public SineWave
{
protected:
    glm::vec2 _origin;

public:
    CircularWave() : _origin(0,0) {}
    virtual ~CircularWave(){}
    glm::vec3 calc(const glm::vec2 & pos,
                   const int count_waves = 1) const;
    void setOrigin(const glm::vec2 & origin)
    {
        _origin = origin;
    }
    static std::shared_ptr<CircularWave> create() { return std::make_shared<CircularWave>(); }
};

class GerstnerWave : public DirectionalWave
{
protected:
    float _steepness;

public:
    GerstnerWave() : _steepness(1.0) {}
    virtual ~GerstnerWave(){}
    glm::vec3 calc(const glm::vec2 & pos,
                   const int count_waves = 1) const;
    void setSteepness(float steepness)
    {
        if(steepness >= 0.0f && steepness <= 1.0f)
            _steepness = steepness;
    }
    static std::shared_ptr<GerstnerWave> create() { return std::make_shared<GerstnerWave>(); }
};

typedef std::shared_ptr<SineWave> SineWavePtr;
typedef std::shared_ptr<DirectionalWave> DirectionalWavePtr;
typedef std::shared_ptr<CircularWave> CircularWavePtr;
typedef std::shared_ptr<GerstnerWave> GerstnerWavePtr;

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