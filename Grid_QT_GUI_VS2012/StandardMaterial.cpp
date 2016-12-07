#include "StandardMaterial.h"
#include "ShaderManager.h"
#include "GlUtils.h"
#include <GL/glew.h>


// default values
StandardMaterial::StandardMaterial() :
    _two_sided_lighting(false),
    _shininess(0),
    _shine_intensity(0),
    _color(Qt::white)
{
    // cache shader in the manager to avoid multiplication of shader instances
    if(!ShaderManager::hasShader("standard"))
    {
        bool success = true;
        GLSLProgramObject program;
        success &= program.attachVertexShader(  "E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\standard_vertex.glsl");
        success &= program.attachFragmentShader("E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\standard_fragment.glsl");
        success &= program.attachFragmentShader("E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\blinn_phong_fragment.glsl");
        success &= program.link();
        ShaderManager::addShader("standard", program);
    }

    _program =  ShaderManager::getShader("standard");
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

void StandardMaterial::setPhongLightingUniforms(const Camera & camera, 
                                                const QVector<Light> & lights)
{
    setUniform("shininess", _shininess);
    setUniform("shine_intensity", _shine_intensity);

    // convert light direction into eye space
    if(!lights.empty())
    {
        glm::vec4 light_dir_eye = camera.viewMat() * glm::vec4(lights[0].direction(), 1);
        glm::vec3 n_light_dir_eye = glm::normalize(glm::vec3(light_dir_eye));
        setUniform("light_dir_eye", n_light_dir_eye);
    }
}

void StandardMaterial::setUniforms(const Camera & camera, 
                                   const QVector<Light> & lights)
{
    setUniform("color", _color);
    setUniform("mvp_mat", camera.mvpMat());
    setUniform("mv_mat", camera.viewMat());

    setPhongLightingUniforms(camera, lights);
}