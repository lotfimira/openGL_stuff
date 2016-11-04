#include "GridMaterial.h"
#include "GlUtils.h"
#include <GL/glew.h>

// default values
GridMaterial::GridMaterial()
{
    bool success = true;

    // TODO: share instance of shader
    GLSLProgramObject program;
    success &= program.attachVertexShader(  "E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\grid_vertex.glsl");
    success &= program.attachFragmentShader("E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\grid_fragment.glsl");
    success &= program.link();

    _program = program;
}

void GridMaterial::initGL()
{
    CLEAR_GL_ERRORS

    glDisable(GL_CULL_FACE);

    CHECK_GL_ERRORS
}

void GridMaterial::cleanupGL()
{
    CLEAR_GL_ERRORS

    glEnable(GL_CULL_FACE);

    CHECK_GL_ERRORS
}

void GridMaterial::setUniforms(const Camera & camera, const QVector<Light> & lights)
{
    setUniform("mvp_mat", camera.mvpMat());
}