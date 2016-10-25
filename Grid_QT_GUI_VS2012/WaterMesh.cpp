#include "WaterMesh.h"
#include "MathUtils.h"


//-----------------------------------------------------------------------------
void WaterMesh::initializeGeometry()
{
    // create vertices
    int size = 100;
    QVector<glm::vec3> pos;
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            float z = (2.0f * sin(20.0f * (float) i / (float)size)) + 
                      (2.0f * sin(20.0f * (float) j / (float)size));
            glm::vec3 p(i - size / 2, z, j - size / 2);
            pos.push_back(p);
        }
    }

    // create triangles indices
    QVector<glm::uvec3> triangles;
    QVector<glm::vec3> normals(size * size);
    for(int j = 0; j < size - 1; ++j)
    {
        int base_index = size * j;

        for(int i = 0; i < size - 1; ++i)
        {
            // 1st triangle of quad
            int idx0 = base_index;
            int idx1 = base_index + 1;
            int idx2 = base_index + 1 + size;

            glm::uvec3 triangle_1(idx0, idx1, idx2);
            triangles.push_back(triangle_1);

            glm::vec3 tri_1_normal = triangleNormal(pos[idx0], 
                                                    pos[idx1], 
                                                    pos[idx2]);
            normals[idx0] += tri_1_normal;
            normals[idx1] += tri_1_normal;
            normals[idx2] += tri_1_normal;

            // 2nd triangle of quad
            idx0 = base_index + size;
            idx1 = base_index;
            idx2 = base_index + 1 + size;

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

    // create OpenGL buffers
    StreamArrayBuffer pos_buffer(pos);
    StreamArrayBuffer normal_buffer(normals);
    ElementArrayBuffer triangle_buffer(triangles);

    _geometry.addAttribute("pos", pos_buffer);
    //_geometry.addAttribute("normals", normal_buffer);
    _geometry.setElements(triangle_buffer);
}

//-----------------------------------------------------------------------------
void WaterMesh::initializeMaterial()
{
    // shaders
    bool success = true;

    GLSLProgramObject program;
    success &= program.attachVertexShader("E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\water_mesh_vertex.glsl");
    success &= program.attachFragmentShader("E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\water_mesh_fragment.glsl");
    success &= program.link();

    _material.setProgram(program);
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
    _material.enable();

    glm::vec4 color(0.0f, 0.0f, 1.0f, 1.0f);
    _material.setUniform("color", color);

    drawTriangles(_geometry, _material, camera);

    _material.disable();
}