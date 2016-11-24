#include "Mesh.h"
#include "GlUtils.h"
#include <QImage>
#include <QGLWidget>
#include <glm/glm.hpp>

//-----------------------------------------------------------------------------
void Mesh::drawTriangles(const Geometry & geometry, 
                         Material & material, 
                         const Camera & camera, 
                         const QVector<Light> & lights)
{
    // bind the program
    material.enable();

    material.setUniforms(camera, lights);

    CLEAR_GL_ERRORS

    QVector<GLuint> attrib_locations;

    // set attributes
    const QMap<QString, StaticArrayBuffer> & static_attributes = geometry.staticAttributes();
    for(const QString & name : static_attributes.keys())
    {
        const ArrayBuffer & buffer = static_attributes[name];

        const GLuint ATTRIB_LOCATION = material.getAttributeLocation(name);
        if(-1 == ATTRIB_LOCATION)
            continue;

        glEnableVertexAttribArray(ATTRIB_LOCATION);
        glBindBuffer(GL_ARRAY_BUFFER, buffer.id());
        glVertexAttribPointer(ATTRIB_LOCATION, 
                              buffer.nbComponentsPerItem(), 
                              buffer.type(), 
                              GL_FALSE, // normalized ??? for colors
                              0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        attrib_locations.push_back(ATTRIB_LOCATION);
    }

    CHECK_GL_ERRORS

    // set attributes
    const QMap<QString, StreamArrayBuffer> & stream_attributes = geometry.streamAttributes();
    for(const QString & name : stream_attributes.keys())
    {
        const ArrayBuffer & buffer = stream_attributes[name];

        const GLuint ATTRIB_LOCATION = material.getAttributeLocation(name);
        if(-1 == ATTRIB_LOCATION)
            continue;

        glEnableVertexAttribArray(ATTRIB_LOCATION);
        glBindBuffer(GL_ARRAY_BUFFER, buffer.id());
        glVertexAttribPointer(ATTRIB_LOCATION, 
                              buffer.nbComponentsPerItem(), 
                              buffer.type(), 
                              GL_FALSE, // normalized ??? for colors
                              0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        attrib_locations.push_back(ATTRIB_LOCATION);
    }

    CHECK_GL_ERRORS

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

    for(const GLuint ATTRIB_LOCATION : attrib_locations)
        glDisableVertexAttribArray(ATTRIB_LOCATION);

    CHECK_GL_ERRORS

    // always surround draw operations with enable and disable material
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
    QVector<glm::uvec3> triangles;
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

            // 2nd triangle of quad
            idx0 = base_index + size;
            idx1 = base_index;
            idx2 = base_index + 1 + size;

            glm::uvec3 triangle_2(idx0, idx1, idx2);
            triangles.push_back(triangle_2);

            base_index++;
        }
    }

    // create OpenGL buffers
    StaticArrayBuffer pos_buffer(pos);
    StaticArrayBuffer color_buffer(colors);
    StaticArrayBuffer tex_coord_buffer(tex_coords);
    ElementArrayBuffer triangle_buffer(triangles);

    _geometry.setStaticAttribute("pos", pos_buffer);
    _geometry.setStaticAttribute("color", color_buffer);
    _geometry.setStaticAttribute("tex_coord", tex_coord_buffer);
    _geometry.setElements(triangle_buffer);
}

void GridAnisotropic::initializeMaterial()
{
    // textures
    Texture2D grid_texture = Texture2D("E:\\4x4grid.png");
    grid_texture.setMipmaps(true);
    grid_texture.setAnisotropic(true);

    _material.addTexture("grid_texture", grid_texture);
}

void GridAnisotropic::draw(const Camera & camera)
{
    drawTriangles(_geometry, _material, camera);
}