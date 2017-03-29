#include "WaterMesh.h"
#include "MathUtils.h"
#include "GLFactory.h"
#include <Windows.h>

#define SIZE 100
#define TILE_SIZE 20
#define TILE_RESOLUTION 60

float t = 0;

glm::vec3 DirectionalWave::calc(const glm::vec2 & pos,
                                const int) const
{
    float omega = (1.0f / _wavelength) * 2 * M_PI; // TODO make this a class so we don't have to calculate this every time
    float t = glm::dot(pos, _direction);

    DWORD ticks = GetTickCount();
    int modulus = _wavelength * 1000;
    int ms = (ticks % modulus);
    float phi = _phase * (2.0f * M_PI) * ((float)ms / (float)(modulus));

    float z = _amplitude * sin( omega * t + phi);

    return glm::vec3(0, 0, z);
}

// derivative along x
float DirectionalWave::dx(const glm::vec2 & pos, const int) const
{
    float omega = (1.0f / _wavelength) * 2 * M_PI; // TODO make this a class so we don't have to calculate this every time

    DWORD ticks = GetTickCount();
    int modulus = _wavelength * 1000;
    int ms = (ticks % modulus);
    float phi = _phase * (2.0f * M_PI) * ((float)ms / (float)(modulus));

    float res = _amplitude * omega * glm::dot(glm::vec2(1,0), _direction) *
                cos( omega * glm::dot(pos, _direction) + phi);

    return res;
}

// derivative along y
float DirectionalWave::dy(const glm::vec2 & pos, const int) const
{
    float omega = (1.0f / _wavelength) * 2 * M_PI; // TODO make this a class so we don't have to calculate this every time

    DWORD ticks = GetTickCount();
    int modulus = _wavelength * 1000;
    int ms = (ticks % modulus);
    float phi = _phase * (2.0f * M_PI) * ((float)ms / (float)(modulus));

    float res = _amplitude * omega * glm::dot(glm::vec2(0,1), _direction) *
                cos( omega * glm::dot(pos, _direction) + phi);

    return res;
}

glm::vec3 CircularWave::calc(const glm::vec2 & pos,
                             const int count_waves) const
{
    float omega = (1.0f / _wavelength) * 2 * M_PI; // TODO make this a class so we don't have to calculate this every time
    float t = glm::length(_origin - pos);

    DWORD ticks = GetTickCount();
    int modulus = _wavelength * 1000;
    int ms = (ticks % modulus);
    float phi = -_phase * (2.0f * M_PI) * ((float)ms / (float)(modulus)); // TODO why negative phase?

    float x = pos.x;
    float y = pos.y;
    float z = _amplitude * sin( omega * t + phi);

    return glm::vec3(0, 0, z);
}

glm::vec3 GerstnerWave::calc(const glm::vec2 & pos, 
                             const int count_waves) const
{
    const float OMEGA = (1.0f / _wavelength) * 2 * M_PI; // TODO make this a class so we don't have to calculate this every time

    DWORD ticks = GetTickCount();
    int modulus = _wavelength * 1000;
    int ms = (ticks % modulus);
    float phi = _phase * (2.0f * M_PI) * ((float)ms / (float)(modulus));
    float t =  glm::dot( pos, _direction);
    float tx = glm::dot( glm::vec2(1,0), _direction);
    float ty = glm::dot( glm::vec2(0,1), _direction);
    float Q = _steepness / (OMEGA * count_waves);

    float x = tx * Q * cos(OMEGA * t + phi);
    float y = ty * Q * cos(OMEGA * t + phi);
    float z = _amplitude * sin(OMEGA * t + phi);

    return glm::vec3(x, y, z);
}


void WaterMesh::computeShape(QVector<glm::vec3> & pos, 
                             QVector<glm::vec3> & normals, 
                             QVector<glm::vec2> & tex_coords,
                             QVector<glm::uvec3> & triangles)
{
    // create vertices
    pos.clear();
    pos.reserve(SIZE * SIZE);
    for(int j = 0; j < SIZE; ++j)
    {
        for(int i = 0; i < SIZE; ++i)
        {
            // sum waves at given point
            glm::vec3 p_wave(i, j, 0);
            for(const SineWavePtr wave : _waves)
            {
                p_wave += wave->calc(glm::vec2(i, j), 
                                     _waves.size());
            }

            // shift to center the grid on (0,0,0)
            glm::vec3 p(p_wave.x - SIZE / 2, 
                        p_wave.z, 
                        p_wave.y - SIZE / 2);

            pos.push_back(p);

            //pos.push_back(glm::vec3(i - SIZE / 2, 0, j - SIZE / 2));
        }
    }

    // TODO do not recomtpute this at each frame
    // texture coordinates
    tex_coords.clear();
    tex_coords.reserve(SIZE * SIZE); 
    for(int j = 0; j < SIZE; ++j)
    {
        float y = (float) j / (float)(TILE_SIZE);

        for(int i = 0; i < SIZE; ++i)
        {
            float x = (float) i / (float)(TILE_SIZE);

            glm::vec2 tex_coord(x, y);
            tex_coords.push_back(tex_coord);
        }
    }

    // TODO do not recomtpute this at each frame
    // create triangles indices
    normals.clear();
    normals.resize(SIZE * SIZE);
    triangles.clear();
    triangles.reserve(SIZE * SIZE);
    for(int j = 0; j < SIZE - 1; ++j)
    {
        int base_index = SIZE * j;

        for(int i = 0; i < SIZE - 1; ++i)
        {
            // 1st triangle of quad
            int idx0 = base_index;
            int idx1 = base_index + 1 + SIZE;
            int idx2 = base_index + 1;

            glm::uvec3 triangle_1(idx0, idx1, idx2);
            triangles.push_back(triangle_1);

            glm::vec3 tri_1_normal = triangleNormal(pos[idx0], 
                                                    pos[idx1], 
                                                    pos[idx2]);
            normals[idx0] += tri_1_normal;
            normals[idx1] += tri_1_normal;
            normals[idx2] += tri_1_normal;

            // 2nd triangle of quad
            idx0 = base_index;
            idx1 = base_index + SIZE;
            idx2 = base_index + 1 + SIZE;

            glm::uvec3 triangle_2(idx0, idx1, idx2);
            triangles.push_back(triangle_2);

            glm::vec3 tri_2_normal = triangleNormal(pos[idx0], 
                                                    pos[idx1], 
                                                    pos[idx2]);
            normals[idx0] += tri_2_normal;
            normals[idx1] += tri_2_normal;
            normals[idx2] += tri_2_normal;

            base_index++;
        }
    }

    // normals
    for(int i = 0; i < normals.size(); ++i)
    {
        normals[i] = glm::normalize(normals[i]);
    }
}

//-----------------------------------------------------------------------------
void WaterMesh::initializeGeometry()
{
    /*
    CircularWavePtr cwave = CircularWave::create();
    cwave->setAmplitude(1);
    cwave->setOrigin(glm::vec2(SIZE / 2, SIZE / 2));
    cwave->setPhase(8);
    cwave->setWavelength(16);

    //_waves.push_back(cwave);

    DirectionalWavePtr dwave1 = DirectionalWave::create();
    dwave1->setAmplitude(2);
    dwave1->setDirection(glm::vec2(1, 0));
    dwave1->setPhase(4); // unit per seconds
    dwave1->setWavelength(16);

    //_waves.push_back(dwave1);

    DirectionalWavePtr dwave2 = DirectionalWave::create();
    dwave1->setAmplitude(2);
    dwave1->setDirection(glm::vec2(1, 1));
    dwave1->setPhase(1); // unit per seconds
    dwave1->setWavelength(19);

    //_waves.push_back(dwave2);*/

    float steepness = 0.8f;
    float amplitude = 0.5f;

    GerstnerWavePtr gwave = GerstnerWave::create();
    gwave->setDirection(glm::vec2(1, 0.5));
    gwave->setAmplitude(amplitude);
    gwave->setWavelength(16.0f);
    gwave->setPhase(2); // unit per seconds
    gwave->setSteepness(steepness);

    _waves.push_back(gwave);
    
    GerstnerWavePtr gwave2 = GerstnerWave::create();
    gwave2->setDirection(glm::vec2(1, 0.8));
    gwave2->setAmplitude(amplitude);
    gwave2->setWavelength(14.0f);
    gwave2->setPhase(2); // unit per seconds
    gwave2->setSteepness(steepness);

    _waves.push_back(gwave2);

    GerstnerWavePtr gwave3 = GerstnerWave::create();
    gwave3->setDirection(glm::vec2(1, 0));
    gwave3->setAmplitude(amplitude);
    gwave3->setWavelength(18.0f);
    gwave3->setPhase(2); // unit per seconds
    gwave3->setSteepness(steepness);

    _waves.push_back(gwave3);

    QVector<glm::vec3> pos;
    QVector<glm::vec3> normals;
    QVector<glm::vec2> tex_coords;
    QVector<glm::uvec3> triangles;

    computeShape(pos, normals, tex_coords, triangles);

    // TODO: the previous syntax was better
    _pos_buffer = createStreamArrayBuffer(pos);

    _geometry.setAttribute("pos", _pos_buffer);
    _geometry.setAttribute("tex_coord", createStaticArrayBuffer(tex_coords));
    _geometry.setElements(ElementArrayBuffer(triangles));


    // tile waves
    DirectionalWavePtr tile_wave_1 = DirectionalWave::create();
    tile_wave_1->setDirection(1, 0);
    tile_wave_1->setAmplitude(1);
    tile_wave_1->setWavelength(10);
    tile_wave_1->setPhase(0); // unit per seconds

    _tile_waves.push_back(tile_wave_1);
}

//-----------------------------------------------------------------------------
void WaterMesh::initializeMaterial()
{
    _material.setDimensions(SIZE, SIZE);
    _material.setShininess(256);
    _material.setShineIntensity(0.7);
    _material.setColor(Qt::blue);
    _material.setTwoSidedLighting(true);

    _wireframe_material.setColor(Qt::white);

    Texture2DPtr t = createTexture("E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Resources\\lena_color.png");
    /*
    QVector<glm::u8vec4> dummy;
    dummy.reserve(SIZE * SIZE);
    for(int y = 0; y < SIZE; ++y)
    {
        for(int x = 0; x < SIZE; ++x)
        {
            glm::u8vec4 color(x, y, 0, 255);
            dummy.push_back(color);
        }
    }
    Texture2DPtr t = createTexture(100,100, dummy);
    t->setWrapping(Texture2D::Wrap::ClampToEdge);
    t->setFiltering(Texture2D::Filter::Nearest);*/

    _texture_material.setTexture(t);
}

WaterMesh::WaterMesh()
{
    initializeGeometry();
    initializeMaterial();
}

WaterMesh::~WaterMesh()
{

}

void WaterMesh::draw(const Camera & camera, const QVector<Light> & lights)
{
    // TODO use this only when drawing the wireframe
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1,1);
    glDisable(GL_CULL_FACE);

    //drawTriangles(_geometry, _material, camera, lights);
    drawTriangles(_geometry, _wireframe_material, camera, lights);
    //drawTriangles(_geometry, _normal_material, camera, lights);
    drawTriangles(_geometry, _stream_texture_material, camera, lights);
    //drawTriangles(_geometry, _normal_texture_material, camera, lights);
    //drawTriangles(_geometry, _texture_material, camera, lights);

    glEnable(GL_CULL_FACE);
    glDisable(GL_POLYGON_OFFSET_FILL);
}

// TODO find a more elegant way to draw wireframe geometry
void WaterMesh::draw(const Camera & camera, 
                     const QVector<Light> & lights, 
                     Material & material)
{
    drawTriangles(_geometry, material, camera, lights);
}

// map normals from [-1, 1] to [0, 1]
QVector<glm::vec3> WaterMesh::mapNormals(const QVector<glm::vec3> & normals)
{
    QVector<glm::vec3> mapped(normals.size());

    for(int i = 0; i < normals.size(); ++i)
    {
        mapped[i] = (normals[i] / 2.0f) + 0.5f;
    }

    return mapped;
}

void WaterMesh::animate()
{
    QVector<glm::vec3> pos;
    QVector<glm::vec3> normals;
    QVector<glm::vec2> tex_coords;
    QVector<glm::uvec3> triangles;

    computeShape(pos, normals, tex_coords, triangles);

    _pos_buffer->update(pos);

    QVector<glm::vec3> mapped_normals = mapNormals(normals);

    _material.setNormals(mapped_normals, SIZE, SIZE);
    _normal_texture_material.setNormals(mapped_normals, SIZE, SIZE);

    QVector<glm::vec3> water_tile = generateTileNormals(TILE_RESOLUTION);
    _stream_texture_material.setTexturePixels(water_tile, TILE_RESOLUTION, TILE_RESOLUTION);
}

QVector<glm::vec3> WaterMesh::generateTileNormals(const int resolution)
{
    QVector<glm::vec3> pixels(resolution * resolution);
    int count_waves = _tile_waves.size();
    int index = 0;

    for(int j = 0; j < resolution; j++)
    {
        for(int i = 0; i <resolution; i++)
        {
            glm::vec2 pos(i, j);
            glm::vec3 normal;

            for(SineWavePtr wave : _tile_waves)
            {
                normal.x += wave->dx(pos, count_waves);
                normal.y += wave->dy(pos, count_waves);
            }

            normal.x = -normal.x;
            normal.y = -normal.y;
            normal.z = 1.0f;
            normal = glm::normalize(normal);

            pixels[index] = normal;

            index++;
        }
    }

    return pixels;
}