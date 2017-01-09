#include "StandardMaterial.h"
#include "ShaderManager.h"
#include "GlUtils.h"
#include "MyException.h"
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

    // TODO how are we gona specify width and height to the material?
    _normal_texture = StreamTexture2D(10, 10, Texture2D::Float);
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

void StandardMaterial::setShininess(float shininess)
{
    _shininess = shininess;
}

void StandardMaterial::setShineIntensity(float shine_intensity)
{
    _shine_intensity = shine_intensity;
}

void StandardMaterial::setDimensions(int width, int height)
{
    _normal_texture = StreamTexture2D(width, height, Texture2D::Float, Texture2D::RGB);
}

void StandardMaterial::setPhongLightingUniforms(const Camera & camera, 
                                                const QVector<Light> & lights)
{
    setUniform("shininess", _shininess);
    setUniform("shine_intensity", _shine_intensity);

    // convert light direction into eye space
    if(!lights.empty())
    {
        glm::vec3 light_dir_eye = camera.normalMat() * (-lights[0].direction());
        light_dir_eye = glm::normalize(light_dir_eye);
        setUniform("light_dir_eye", light_dir_eye);
    }

    setUniform("camera_pos", camera.pos());
}

void StandardMaterial::setUniforms(const Camera & camera, 
                                   const QVector<Light> & lights)
{
    setUniform("color", _color);
    setUniform("mvp_mat", camera.mvpMat());
    setUniform("normal_mat", camera.normalMat());

    setPhongLightingUniforms(camera, lights);
}

void StandardMaterial::setNormals(const QVector<glm::vec3> & normals, 
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