#include "NormalMaterial.h"
#include "ShaderManager.h"

//-----------------------------------------------------------------------------
NormalMaterial::NormalMaterial() : _color(Qt::green), _normal_length(1.0f)
{
    // TODO: duplicated code in every material

    // cache shader in the manager to avoid multiplication of shader instances
    if(!ShaderManager::hasShader("normal"))
    {
        bool success = true;
        GLSLProgramObject program;
        success &= program.attachVertexShader(  "E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\normal_vertex.glsl");
        success &= program.attachGeometryShader("E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\normal_geometry.glsl");
        success &= program.attachFragmentShader("E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\normal_fragment.glsl");
        success &= program.link();
        ShaderManager::addShader("normal", program);
    }

    _program =  ShaderManager::getShader("normal");
}

void NormalMaterial::initGL()
{
    glLineWidth(1.0f);
    glColor4f(_color.redF(), _color.greenF(), _color.blueF(), _color.alphaF());
}

void NormalMaterial::cleanupGL()
{

}

void NormalMaterial::setUniforms(const Camera & camera, 
                                 const QVector<Light> & lights)
{
    setUniform("color", _color);
    setUniform("mvp_mat", camera.mvpMat());
    setUniform("normal_length", _normal_length);
}

void NormalMaterial::setColor(const QColor & color)
{
    _color = color;
}

void NormalMaterial::setNormalLength(float length)
{
    _normal_length = length;
}

