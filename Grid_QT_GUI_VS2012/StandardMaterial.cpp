#include "StandardMaterial.h"
#include "GlUtils.h"
#include <GL/glew.h>

// default values
StandardMaterial::StandardMaterial() :
    _two_sided_lighting(false),
    _shininess(0),
    _shine_intensity(0),
    _color(Qt::white)
{
    bool success = true;

    // TODO: share instance of shader
    GLSLProgramObject program;
    success &= program.attachVertexShader(  "E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\water_mesh_vertex.glsl");
    success &= program.attachFragmentShader("E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\water_mesh_fragment.glsl");
    success &= program.attachFragmentShader("E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\blinn_phong_fragment.glsl");
    success &= program.link();

    _program = program;
}

void StandardMaterial::initGL()
{
    CLEAR_GL_ERRORS

    if(_two_sided_lighting)
        glDisable(GL_CULL_FACE);
    else
        glEnable(GL_CULL_FACE);

    CHECK_GL_ERRORS
}

void StandardMaterial::cleanupGL()
{
    CLEAR_GL_ERRORS

    glEnable(GL_CULL_FACE);

    CHECK_GL_ERRORS
}

void StandardMaterial::setColor(const QColor & color)
{
    _color = color;
}

void StandardMaterial::setUniforms(const Camera & camera, const QVector<Light> & lights)
{
    setUniform("color", _color);
    setUniform("shininess", _shininess);
    setUniform("shine_intensity", _shine_intensity);

    // convert light direction into eye space
    if(!lights.empty())
    {
        glm::vec4 light_dir_eye = camera.viewMat() * glm::vec4(lights[0].direction(), 1);
        setUniform("light_dir", glm::vec3(light_dir_eye));
    }
    setUniform("mvp_mat", camera.mvpMat());
    setUniform("mv_mat", camera.viewMat());
}