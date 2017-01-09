#include "Material.h"
#include "GlUtils.h"
#include "MyException.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void Material::enable()
{
    if(!_textures.isEmpty())
        enableTextures();

    initGL();

    _program.bind();
}

void Material::disable()
{
    disableTextures();

    cleanupGL();

    _program.unbind();
}

void Material::setUniform(const QString & name, glm::mat4 & matrix)
{
    _program.setUniformMatrix(name.toStdString().c_str(), glm::value_ptr(matrix), 4);
}

void Material::setUniform(const QString & name, glm::mat3& matrix)
{
    _program.setUniformMatrix(name.toStdString().c_str(), glm::value_ptr(matrix), 3);
}

void Material::setUniform(const QString & name, glm::vec4 & v)
{
    _program.setUniform(name.toStdString().c_str(), glm::value_ptr(v), 4);
}

void Material::setUniform(const QString & name, glm::vec3 & v)
{
    _program.setUniform(name.toStdString().c_str(), glm::value_ptr(v), 3);
}

void Material::setUniform(const QString & name, float & v)
{
    _program.setUniform(name.toStdString().c_str(), &v, 1);
}

void Material::setUniform(const QString & name, QColor & color)
{
    glm::vec4 c(color.redF(), color.greenF(), color.blueF(), color.alphaF());
    _program.setUniform(name.toStdString().c_str(), glm::value_ptr(c), 4);
}

void Material::addTexture(const QString & name, const Texture2DPtr texture)
{
    _textures[name] = texture;
}

void Material::enableTextures()
{
    CLEAR_GL_ERRORS

    if(!_textures.empty())
    {
        glEnable(GL_TEXTURE_2D);
    }

    int texture_unit = GL_TEXTURE0;
    for(auto it = _textures.begin(); it != _textures.end(); it++)
    {
        const QString & name = it.key();
        const Texture2DPtr texture = it.value();

        _program.setTextureUnit(name.toStdString(), texture_unit - GL_TEXTURE0);

        glActiveTexture(texture_unit);
        glBindTexture(GL_TEXTURE_2D, texture->id());
        ++texture_unit;
    }

    glActiveTexture(GL_TEXTURE0);

    CHECK_GL_ERRORS
}

void Material::disableTextures()
{
    CLEAR_GL_ERRORS

    glDisable(GL_TEXTURE_2D);

    int texture_unit = GL_TEXTURE0;
    for(const Texture2DPtr & texture : _textures)
    {
        glActiveTexture(texture_unit);
        glBindTexture(GL_TEXTURE_2D, 0);
        ++texture_unit;
    }

    glActiveTexture(GL_TEXTURE0);

    CHECK_GL_ERRORS
}

void Material::clean()
{
    _textures.clear();
}

GLuint Material::getAttributeLocation(const QString & name) const
{
    return _program.getAttribLocation(name.toStdString().c_str());
}

Texture2DPtr Material::texture(const QString & name)
{
    if(_textures.contains(name))
        return _textures[name];

    throw new MyException("Material::texture() Texture not found");
}