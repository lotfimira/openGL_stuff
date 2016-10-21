#include "Mesh.h"
#include "GlUtils.h"
#include <QImage>
#include <QGLWidget>
#include <glm/glm.hpp>

void Mesh::drawTriangles(const Geometry & geometry, Material & material, const Camera & camera)
{
    // always surround material operations with enable and disable
    material.enable();

    material.setAttributes(geometry);

    material.setUniform("mvp_mat", camera.mvpMat());

    CLEAR_GL_ERRORS

    if(geometry.hasElements())
    {
        const ElementArrayBuffer & elements = geometry.elements();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements.id());
        glDrawElements(GL_TRIANGLES, elements.nbElements(), GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, geometry.nbVertices());
    }

    CHECK_GL_ERRORS

    // always surround material operations with enable and disable
    material.disable();
}

//-----------------------------------------------------------------------------
GroundPlaneAnisotropic::GroundPlaneAnisotropic()
{
    _texture2D = Texture2D("E:\\4x4grid.png");
    _texture2D.setMipmaps(true);
    _texture2D.setAnisotropic(true);
}

GroundPlaneAnisotropic::~GroundPlaneAnisotropic()
{

}

void GroundPlaneAnisotropic::draw(const Camera & camera)
{
    CLEAR_GL_ERRORS

    // no lighting
    glDisable(GL_LIGHTING);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _texture2D.id());

    CHECK_GL_ERRORS

    // white
    glColor4f(1, 1, 1, 1);

    // quad facing the camera
    int s = 100;
    int y = 0;
    int nb_repeat = 20;
    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);
    glVertex3f(s, y, s);

    glTexCoord2f(0, nb_repeat);
    glVertex3f(s, y, -s);

    glTexCoord2f(nb_repeat, nb_repeat);
    glVertex3f(-s, y, -s);

    glTexCoord2f(nb_repeat, 0);
    glVertex3f(-s, y, s);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    CHECK_GL_ERRORS
}

//-----------------------------------------------------------------------------
GridAnisotropic::GridAnisotropic()
{
    initializeGeometry();
    initializeMaterial();
}

GridAnisotropic::~GridAnisotropic()
{
}

void GridAnisotropic::initializeGeometry()
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

    // create colors
    QVector<glm::vec4> colors;
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            glm::vec4 p((float)i / (float)size , 0, (float)j / (float)size, 1);
            colors.push_back(p);
        }
    }

    // create texture coordinates
    QVector<glm::vec2> tex_coords;
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            glm::vec2 coord(i, j);
            tex_coords.push_back(coord);
        }
    }

    // create triangles indices
    QVector<GLuint> triangles;
    for(int j = 0; j < size - 1; ++j)
    {
        int base_index = size * j;

        for(int i = 0; i < size - 1; ++i)
        {
            // 1st triangle of quad
            int idx0 = base_index;
            int idx1 = base_index + 1;
            int idx2 = base_index + 1 + size;

            triangles.push_back(idx0);
            triangles.push_back(idx1);
            triangles.push_back(idx2);

            // 2nd triangle of quad
            idx0 = base_index + size;
            idx1 = base_index;
            idx2 = base_index + 1 + size;

            triangles.push_back(idx0);
            triangles.push_back(idx1);
            triangles.push_back(idx2);

            base_index++;
        }
    }

    // create OpenGL buffers
    _geometry.addAttribute("pos", pos);
    _geometry.addAttribute("color", colors);
    _geometry.addAttribute("tex_coord", tex_coords);
    _geometry.setElements(triangles);
}

void GridAnisotropic::initializeMaterial()
{
    // textures
    Texture2D grid_texture = Texture2D("E:\\4x4grid.png");
    grid_texture.setMipmaps(true);
    grid_texture.setAnisotropic(true);

    _material.addTexture(grid_texture);

    // shaders
    bool success = true;

    GLSLProgramObject program;
    success &= program.attachVertexShader("E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\grid_vertex.glsl");
    success &= program.attachFragmentShader("E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\grid_fragment.glsl");
    success &= program.link();

    _material.setProgram(program);
}

void GridAnisotropic::draw(const Camera & camera)
{
    drawTriangles(_geometry, _material, camera);
}