#include "Mesh.h"
#include "GlUtils.h"
#include <QImage>
#include <QGLWidget>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>

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
GridAnisotropic::GridAnisotropic()
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
    _pos_buffer = ArrayBuffer(pos);
    _color_buffer = ArrayBuffer(colors);
    _tex_coord_buffer = ArrayBuffer(tex_coords);
    _index_buffer = ElementArrayBuffer(triangles);
}

GridAnisotropic::~GridAnisotropic()
{
    _pos_buffer.clean();
    _color_buffer.clean();
    _tex_coord_buffer.clean();
    _index_buffer.clean();
}

void GridAnisotropic::draw(const Camera & camera)
{
    CLEAR_GL_ERRORS;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _texture2D.id());

    glBindBuffer(GL_ARRAY_BUFFER, _pos_buffer.id());
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    glEnableClientState(GL_VERTEX_ARRAY);
    CHECK_GL_ERRORS;

    glBindBuffer(GL_ARRAY_BUFFER, _color_buffer.id());
    glColorPointer(4, GL_FLOAT, 0, NULL);
    glEnableClientState(GL_COLOR_ARRAY);
    CHECK_GL_ERRORS;

    glBindBuffer(GL_ARRAY_BUFFER, _tex_coord_buffer.id());
    glTexCoordPointer(2, GL_FLOAT, 0, NULL);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    CHECK_GL_ERRORS;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer.id());
    CHECK_GL_ERRORS;

    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glDrawElements(GL_TRIANGLES, _index_buffer.nbElements(), GL_UNSIGNED_INT, 0);
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
    glBindBuffer(GL_ARRAY_BUFFER, _pos_buffer.id());
    glVertexAttribPointer(POS_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0, 0);
    CHECK_GL_ERRORS

    glEnableVertexAttribArray(COLOR_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, _color_buffer.id());
    glVertexAttribPointer(COLOR_ATTRIB, 4, GL_FLOAT, GL_FALSE, 0, 0);
    CHECK_GL_ERRORS

    glEnableVertexAttribArray(TEX_COORD_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, _tex_coord_buffer.id());
    glVertexAttribPointer(TEX_COORD_ATTRIB, 2, GL_FLOAT, GL_FALSE, 0, 0);
    CHECK_GL_ERRORS

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer.id());
    CHECK_GL_ERRORS;

    glDrawElements(GL_TRIANGLES, _index_buffer.nbElements(), GL_UNSIGNED_INT, 0);

    _program.unbind();

    glDisableVertexAttribArray(POS_ATTRIB);
    glDisableVertexAttribArray(COLOR_ATTRIB);
    glDisableVertexAttribArray(TEX_COORD_ATTRIB);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}