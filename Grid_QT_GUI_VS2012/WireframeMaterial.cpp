#include "WireframeMaterial.h"
#include "GlUtils.h"
#include "ShaderManager.h"

#define WIREFRAME_SHADER_NAME "wireframe"

WireframeMaterial::WireframeMaterial() :
    _color(Qt::white)
{
    // cache shader in the manager to avoid multiplication of shader instances
    if(!ShaderManager::hasShader(WIREFRAME_SHADER_NAME))
    {
        bool success = true;
        GLSLProgramObject program;
        success &= program.attachVertexShader(  "E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\wireframe_vertex.glsl");
        success &= program.attachFragmentShader("E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\wireframe_fragment.glsl");
        success &= program.link();
        ShaderManager::addShader(WIREFRAME_SHADER_NAME, program);
    }

    _program =  ShaderManager::getShader(WIREFRAME_SHADER_NAME);
}

void WireframeMaterial::initGL()
{
    CLEAR_GL_ERRORS

    glLineWidth(1.0f);
    glColor4f(_color.redF(), _color.greenF(), _color.blueF(), _color.alphaF());
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    CHECK_GL_ERRORS
}

void WireframeMaterial::cleanupGL()
{
    CLEAR_GL_ERRORS

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    CHECK_GL_ERRORS
}

void WireframeMaterial::setUniforms(const Camera & camera, const QVector<Light> & lights)
{
    setUniform("color", _color);
    setUniform("mvp_mat", camera.mvpMat());
}

void WireframeMaterial::setColor(const QColor & color)
{
    _color = color;
}