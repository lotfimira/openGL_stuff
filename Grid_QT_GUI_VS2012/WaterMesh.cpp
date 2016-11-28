#include "WaterMesh.h"
#include "MathUtils.h"
#include "GLFactory.h"
#include <Windows.h>

#define SIZE 100

void computeShape(QVector<glm::vec3> & pos, 
                  QVector<glm::vec3> & normals, 
                  QVector<glm::uvec3> & triangles)
{
    int t = GetTickCount();

    // create vertices
    pos.clear();
    pos.reserve(SIZE * SIZE);
    for(int i = 0; i < SIZE; ++i)
    {
        for(int j = 0; j < SIZE; ++j)
        {
            float z = (2.0f * sin((20.0f * (float) i + t) / (float)SIZE)) + 
                      (2.0f * sin(20.0f * (float) j / (float)SIZE));
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
}

WaterMesh::WaterMesh()
{
    initializeGeometry();
    initializeMaterial();
}

WaterMesh::~WaterMesh()
{

}

void WaterMesh::draw(const Camera & camera)
{
    _material.setColor(Qt::blue);

    drawTriangles(_geometry, _material, camera);
}

void WaterMesh::animate()
{
    QVector<glm::vec3> pos;
    QVector<glm::vec3> normals;
    QVector<glm::uvec3> triangles;

    computeShape(pos, normals, triangles);

    _pos_buffer->update(pos);
    _normal_buffer->update(normals);

    printf("%.2f\r", pos[0].y);
}