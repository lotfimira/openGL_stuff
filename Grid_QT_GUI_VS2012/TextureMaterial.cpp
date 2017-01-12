#include "TextureMaterial.h"
#include "ShaderManager.h"

//-----------------------------------------------------------------------------
TextureMaterial::TextureMaterial()
{
    // TODO: duplicated code in every material

    // cache shader in the manager to avoid multiplication of shader instances
    if(!ShaderManager::hasShader("texture"))
    {
        bool success = true;
        GLSLProgramObject program;
        success &= program.attachVertexShader(  "E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\texture_vertex.glsl");
        success &= program.attachFragmentShader("E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\texture_fragment.glsl");
        success &= program.link();
        ShaderManager::addShader("texture", program);
    }

    _program =  ShaderManager::getShader("texture");
}

void TextureMaterial::initGL()
{
    glColor4f(1,1,1,1);
}

void TextureMaterial::cleanupGL()
{

}

void TextureMaterial::setUniforms(const Camera & camera, 
                                 const QVector<Light> & lights)
{
    setUniform("mvp_mat", camera.mvpMat());
}

void TextureMaterial::setTexture(const Texture2DPtr texture)
{
    addTexture("main_texture", texture);
}