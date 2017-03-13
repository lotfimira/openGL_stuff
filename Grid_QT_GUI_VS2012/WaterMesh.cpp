#include "WaterMesh.h"
#include "MathUtils.h"
#include "GLFactory.h"
#include <Windows.h>

#define SIZE 100

float t = 0;

glm::vec3 DirectionalWave::calc(const glm::vec2 & pos) const
{
    float omega = (1.0f / _wavelength) * 2 * M_PI; // TODO make this a class so we don't have to calculate this every time
    float t = glm::dot(pos, _direction);

    DWORD ticks = GetTickCount();
    int modulus = _wavelength * 1000;
    int ms = (ticks % modulus);
    float phi = _phase * (2.0f * M_PI) * ((float)ms / (float)(modulus));

    float x = pos.x;
    float y = pos.y;
    float z = _amplitude * sin( omega * t + phi);

    return glm::vec3(x, y, z);
}

glm::vec3 CircularWave::calc(const glm::vec2 & pos) const
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

    return glm::vec3(x, y, z);
}

glm::vec3 GerstnerWave::calc(const glm::vec2 & pos) const
{
    const float OMEGA = (1.0f / _wavelength) * 2 * M_PI; // TODO make this a class so we don't have to calculate this every time

    DWORD ticks = GetTickCount();
    int modulus = _wavelength * 1000;
    int ms = (ticks % modulus);
    float phi = _phase * (2.0f * M_PI) * ((float)ms / (float)(modulus));
    float t = glm::dot(pos, _direction);
    float tx = glm::dot( glm::vec2(1,0), _direction);
    float ty = glm::dot( glm::vec2(0,1), _direction);

    float x = pos.x + tx * (1 / OMEGA) * cos(OMEGA * t + phi);
    float y = pos.y + ty * (1 / OMEGA) * cos(OMEGA * t + phi);
    float z = _amplitude * sin(OMEGA * t + phi);

    return glm::vec3(x, y, z);
}


void WaterMesh::computeShape(QVector<glm::vec3> & pos, 
                             QVector<glm::vec3> & normals, 
                             QVector<glm::vec2> & tex_coords,
                             QVector<glm::uvec3> & triangles)
{
    t += 0.1f;
    DWORD time = GetTickCount();
    float tf = (float)time / 1000.0f;

    // create vertices
    pos.clear();
    pos.reserve(SIZE * SIZE);
    for(int j = 0; j < SIZE; ++j)
    {
        for(int i = 0; i < SIZE; ++i)
        {
            // sum waves at given point
            glm::vec3 p_wave;
            for(const SineWavePtr wave : _waves)
            {
                p_wave += wave->calc(glm::vec2(i, j));
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
        float y = (float) j / (float)(SIZE - 1);

        for(int i = 0; i < SIZE; ++i)
        {
            float x = (float) i / (float)(SIZE - 1);

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

    GerstnerWavePtr gwave = GerstnerWave::create();
    gwave->setDirection(glm::vec2(1, 1));
    gwave->setAmplitude(4.0f);
    gwave->setWavelength(16.0f);
    gwave->setPhase(2); // unit per seconds

    _waves.push_back(gwave);

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

    drawTriangles(_geometry, _material, camera, lights);
    drawTriangles(_geometry, _wireframe_material, camera, lights);
    //drawTriangles(_geometry, _normal_material, camera, lights);
    //drawTriangles(_geometry, _stream_texture_material, camera, lights);
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
    _stream_texture_material.setTexturePixels(mapped_normals, SIZE, SIZE);
}