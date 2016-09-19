#include "Mesh.h"
#include "GlUtils.h"
#include <QImage>
#include <QGLWidget>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>


GLuint Mesh::createBuffer(GLenum target, GLsizeiptr size, const GLvoid * data)
{
    CLEAR_GL_ERRORS

    GLuint buffer = 0;
    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, GL_STATIC_DRAW);
    glBindBuffer(target, 0);

    CHECK_GL_ERRORS;

    return buffer;
}

GLuint Mesh::createArrayBuffer(GLsizeiptr size, const GLvoid * data)
{
    return createBuffer(GL_ARRAY_BUFFER, size, data);
}

GLuint Mesh::createElementArrayBuffer(GLsizeiptr size, const GLvoid * data)
{
    return createBuffer(GL_ELEMENT_ARRAY_BUFFER, size, data);
}

void Mesh::deleteBuffer(GLuint & buffer)
{
    if(glIsBuffer(buffer))
    {
        glDeleteBuffers(1, &buffer);
    }

    buffer = 0;
}

GroundPlaneAnisotropic::GroundPlaneAnisotropic()
{
    _texture2D.setMipmaps(true);
    _texture2D.setAnisotropic(true);
    _texture2D.load("E:\\4x4grid.png");
}

GroundPlaneAnisotropic::~GroundPlaneAnisotropic()
{

}

void GroundPlaneAnisotropic::draw()
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
GridAnisotropic::GridAnisotropic() : 
    _pos_buffer(0), _index_buffer(0), _color_buffer(0), _tex_coord_buffer(0)
{
    _texture2D.setMipmaps(true);
    _texture2D.setAnisotropic(true);
    _texture2D.load("E:\\4x4grid.png");

    // create vertices
    int size = 100;
    QVector<glm::vec3> pos;
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            glm::vec3 p(i - size / 2, 0, j - size / 2);
            pos.push_back(p);
        }
    }

    // create colors
    QVector<glm::vec4> colors;
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            glm::vec4 p((float)i / (float)size , 0, (float)j / (float)size, 0);
            colors.push_back(p);
        }
    }

    // create texture coordinates

    // create triangles indices
    QVector<GLuint> indices;
    for(int j = 0; j < size - 1; ++j)
    {
        int base_index = size * j;

        for(int i = 0; i < size - 1; ++i)
        {
            // 1st triangle of quad
            int idx0 = base_index;
            int idx1 = base_index + 1;
            int idx2 = base_index + 1 + size;

            indices.push_back(idx0);
            indices.push_back(idx1);
            indices.push_back(idx2);

            // 2nd triangle of quad
            idx0 = base_index + size;
            idx1 = base_index;
            idx2 = base_index + 1 + size;

            indices.push_back(idx0);
            indices.push_back(idx1);
            indices.push_back(idx2);

            base_index++;
        }
    }

    // load buffer in OpenGL
    _pos_buffer = createArrayBuffer(pos.size() * sizeof(glm::vec3), &pos[0]);
    _color_buffer = createArrayBuffer(colors.size() * sizeof(glm::vec4), &colors[0]);
    _index_buffer = createElementArrayBuffer(indices.size() * sizeof(GLuint), &indices[0]);

    _vert_count = pos.size();
    _index_count = indices.size();
}

GridAnisotropic::~GridAnisotropic()
{
    deleteBuffer(_pos_buffer);
    deleteBuffer(_index_buffer);
    deleteBuffer(_color_buffer);
    deleteBuffer(_tex_coord_buffer);

    _vert_count = 0;
}

void GridAnisotropic::draw()
{
    CLEAR_GL_ERRORS;

    glBindBuffer(GL_ARRAY_BUFFER, _pos_buffer);
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    glEnableClientState(GL_VERTEX_ARRAY);
    CHECK_GL_ERRORS;

    glBindBuffer(GL_ARRAY_BUFFER, _color_buffer);
    glColorPointer(4, GL_FLOAT, 0, NULL);
    glEnableClientState(GL_COLOR_ARRAY);
    CHECK_GL_ERRORS;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);
    CHECK_GL_ERRORS;

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glDrawElements(GL_TRIANGLES, _index_count, GL_UNSIGNED_INT, 0);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}