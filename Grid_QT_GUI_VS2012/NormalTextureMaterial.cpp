#include "NormalTextureMaterial.h"
#include "ShaderManager.h"

//-----------------------------------------------------------------------------
NormalTextureMaterial::NormalTextureMaterial() : _color(Qt::green), _normal_length(1.0f)
{
    // TODO: duplicated code in every material

    // cache shader in the manager to avoid multiplication of shader instances
    if(!ShaderManager::hasShader("normal_texture"))
    {
        bool success = true;
        GLSLProgramObject program;
        success &= program.attachVertexShader(  "E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\normal_texture_vertex.glsl");
        success &= program.attachGeometryShader("E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\normal_texture_geometry.glsl");
        success &= program.attachFragmentShader("E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\normal_texture_fragment.glsl");
        success &= program.link();
        ShaderManager::addShader("normal_texture", program);
    }

    _program =  ShaderManager::getShader("normal_texture");
}

void NormalTextureMaterial::initGL()
{
    glLineWidth(1.0f);
    glColor4f(_color.redF(), _color.greenF(), _color.blueF(), _color.alphaF());
}

void NormalTextureMaterial::cleanupGL()
{

}

void NormalTextureMaterial::setUniforms(const Camera & camera, 
                                 const QVector<Light> & lights)
{
    setUniform("color", _color);
    setUniform("mvp_mat", camera.mvpMat());
    setUniform("normal_length", _normal_length);
}

void NormalTextureMaterial::setColor(const QColor & color)
{
    _color = color;
}

void NormalTextureMaterial::setNormalLength(float length)
{
    _normal_length = length;
}

//-----------------------------------------------------------------------------
void NormalTextureMaterial::setNormals(const QVector<glm::vec3> & normals, 
                                       int width, int height)
{
    if(!_textures.contains("normal_texture"))
    {
        addTexture("normal_texture", createStreamTexture(width, height, normals));
    }
    else
    {
        Texture2DPtr t = texture("normal_texture");
        StreamTexture2DPtr normal_texture = std::static_pointer_cast<StreamTexture2D>(t);
        normal_texture->update(normals, width, height);
    }
}