#include "StreamTextureMaterial.h"
#include "ShaderManager.h"

//-----------------------------------------------------------------------------
StreamTextureMaterial::StreamTextureMaterial()
{
    // TODO: duplicated code in every material

    // cache shader in the manager to avoid multiplication of shader instances
    if(!ShaderManager::hasShader("stream_texture"))
    {
        bool success = true;
        GLSLProgramObject program;
        success &= program.attachVertexShader(  "E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\stream_texture_vertex.glsl");
        success &= program.attachFragmentShader("E:\\Dev\\Grid\\Grid_QT_GUI_VS2012\\Grid_QT_GUI_VS2012\\Shaders\\stream_texture_fragment.glsl");
        success &= program.link();
        ShaderManager::addShader("stream_texture", program);
    }

    _program =  ShaderManager::getShader("stream_texture");
}

void StreamTextureMaterial::initGL()
{
    glColor4f(1,1,1,1);
}

void StreamTextureMaterial::cleanupGL()
{

}

void StreamTextureMaterial::setUniforms(const Camera & camera, 
                                 const QVector<Light> & lights)
{
    setUniform("mvp_mat", camera.mvpMat());
}

//-----------------------------------------------------------------------------
void StreamTextureMaterial::setTexturePixels(const QVector<glm::vec3> & normals, 
                                             int width, int height)
{
    if(!_textures.contains("main_texture"))
    {
        addTexture("main_texture", createStreamTexture(width, height, normals));
    }
    else
    {
        Texture2DPtr t = getTexture("main_texture");
        StreamTexture2DPtr texture = std::static_pointer_cast<StreamTexture2D>(t);
        texture->update(normals, width, height);
    }
}