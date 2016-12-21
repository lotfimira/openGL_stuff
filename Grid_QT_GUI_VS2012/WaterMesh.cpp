#include "WaterMesh.h"
#include "MathUtils.h"
#include "GLFactory.h"
#include <Windows.h>

#define SIZE 100

float t = 0;

float SineWave::calc(float x, float y, float t) const
{
    glm::vec2 point_dir = glm::vec2(x, y);

    //return amplitude * sin( glm::dot(direction, point_dir) * 
                            //omega + t * phase);
    return amplitude * sin( glm::dot(direction, point_dir) / omega + t * phase);
}

void WaterMesh::computeShape(QVector<glm::vec3> & pos, 
                             QVector<glm::vec3> & normals, 
                             QVector<glm::uvec3> & triangles)
{
    t += 0.1f;

    // create vertices
    pos.clear();
    pos.reserve(SIZE * SIZE);
    for(int i = 0; i < SIZE; ++i)
    {
        for(int j = 0; j < SIZE; ++j)
        {
            //float z = (2.0f * sin((20.0f * (float) i + t) / (float)SIZE));

            float z = 0;
            for(const SineWave & wave : _waves)
            {
                z += wave.calc(i, j, t);
            }

            glm::vec3 p(i - SIZE / 2, z, j - SIZE / 2);
            pos.push_back(p);
        }
    }

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
            int idx1 = base_index + 1;
            int idx2 = base_index + 1 + SIZE;

            glm::uvec3 triangle_1(idx0, idx1, idx2);
            triangles.push_back(triangle_1);

            glm::vec3 tri_1_normal = triangleNormal(pos[idx0], 
                                                    pos[idx1], 
                                                    pos[idx2]);
            normals[idx0] += tri_1_normal;
            normals[idx1] += tri_1_normal;
            normals[idx2] += tri_1_normal;

            // 2nd triangle of quad
            idx0 = base_index + SIZE;
            idx1 = base_index;
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
    SineWave wave;
    wave.amplitude = 2;
    wave.direction = glm::vec2(1, 0);
    wave.phase = 0.2;
    wave.omega = 4;

    _waves.push_back(wave);

    wave.amplitude = 1;
    wave.direction = glm::vec2(1, 1);
    wave.phase = 0.3;
    wave.omega = 2;

    _waves.push_back(wave);

    QVector<glm::vec3> pos;
    QVector<glm::vec3> normals;
    QVector<glm::uvec3> triangles;

    computeShape(pos, normals, triangles);

    _pos_buffer = createStreamArrayBuffer(pos);
    _normal_buffer = createStreamArrayBuffer(normals);

    _geometry.setAttribute("pos", _pos_buffer);
    _geometry.setAttribute("normal", _normal_buffer);
    _geometry.setElements(ElementArrayBuffer(triangles));
}

//-----------------------------------------------------------------------------
void WaterMesh::initializeMaterial()
{
    _material.setShininess(256);
    _material.setShineIntensity(0.7);
    _material.setColor(Qt::blue);

    _wireframe_material.setColor(Qt::white);
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

    drawTriangles(_geometry, _material, camera, lights);
    drawTriangles(_geometry, _wireframe_material, camera, lights);

    glDisable(GL_POLYGON_OFFSET_FILL);
}

// TODO find a more elegant way to draw wireframe geometry
void WaterMesh::draw(const Camera & camera, 
                     const QVector<Light> & lights, 
                     Material & material)
{
    drawTriangles(_geometry, material, camera, lights);
}

void WaterMesh::animate()
{
    QVector<glm::vec3> pos;
    QVector<glm::vec3> normals;
    QVector<glm::uvec3> triangles;

    computeShape(pos, normals, triangles);

    _pos_buffer->update(pos);
    _normal_buffer->update(normals);
}