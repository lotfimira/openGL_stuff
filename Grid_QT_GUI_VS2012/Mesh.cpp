#include "Mesh.h"
#include "GlUtils.h"
#include <QImage>
#include <QGLWidget>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>


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
    _tex_coord_buffer = createArrayBuffer(tex_coords.size() * sizeof(glm::vec2), &tex_coords[0]);
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

void GridAnisotropic::draw(const Camera & camera)
{
    CLEAR_GL_ERRORS;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _texture2D.id());

    glBindBuffer(GL_ARRAY_BUFFER, _pos_buffer);
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    glEnableClientState(GL_VERTEX_ARRAY);
    CHECK_GL_ERRORS;

    glBindBuffer(GL_ARRAY_BUFFER, _color_buffer);
    glColorPointer(4, GL_FLOAT, 0, NULL);
    glEnableClientState(GL_COLOR_ARRAY);
    CHECK_GL_ERRORS;

    glBindBuffer(GL_ARRAY_BUFFER, _tex_coord_buffer);
    glTexCoordPointer(2, GL_FLOAT, 0, NULL);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    CHECK_GL_ERRORS;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);
    CHECK_GL_ERRORS;

    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glDrawElements(GL_TRIANGLES, _index_count, GL_UNSIGNED_INT, 0);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

ShadedGridAnisotropic::ShadedGridAnisotropic()
{
    bool success = true;

    success &= _program.attachVertexShader("E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\grid_vertex.glsl");
    success &= _program.attachFragmentShader("E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\grid_fragment.glsl");
    success &= _program.link();
}

ShadedGridAnisotropic::~ShadedGridAnisotropic()
{

}

void ShadedGridAnisotropic::draw(const Camera & camera)
{
    CLEAR_GL_ERRORS

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _texture2D.id());

    _program.bind();

    // TODO: is this class caching the location of uniforms and attribute
    // so it does not have to do a get every time
    glm::mat4 mvp = camera.mvpMat();
    _program.setUniformMatrix("mvp_mat", glm::value_ptr(mvp), 4);

    const GLuint POS_ATTRIB = _program.getAttribLocation("pos");
    const GLuint COLOR_ATTRIB   = _program.getAttribLocation("color");
    const GLuint TEX_COORD_ATTRIB  = _program.getAttribLocation("tex_coord");

    glEnableVertexAttribArray(POS_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, _pos_buffer);
    glVertexAttribPointer(POS_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0, 0);
    CHECK_GL_ERRORS

    glEnableVertexAttribArray(COLOR_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, _color_buffer);
    glVertexAttribPointer(COLOR_ATTRIB, 4, GL_FLOAT, GL_FALSE, 0, 0);
    CHECK_GL_ERRORS

    glEnableVertexAttribArray(TEX_COORD_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, _tex_coord_buffer);
    glVertexAttribPointer(TEX_COORD_ATTRIB, 2, GL_FLOAT, GL_FALSE, 0, 0);
    CHECK_GL_ERRORS

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);
    CHECK_GL_ERRORS;

    glDrawElements(GL_TRIANGLES, _index_count, GL_UNSIGNED_INT, 0);

    _program.unbind();

    glDisableVertexAttribArray(POS_ATTRIB);
    glDisableVertexAttribArray(COLOR_ATTRIB);
    glDisableVertexAttribArray(TEX_COORD_ATTRIB);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}