#include "Material.h"
#include "GlUtils.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void Material::enable()
{
    if(!_textures.isEmpty())
        enableTextures();

    _program.bind();
}

void Material::disable()
{
    disableTextures();

    disableAttributes();

    _program.unbind();
}

void Material::disableAttributes()
{
    CLEAR_GL_ERRORS

    for(GLuint attribute : _attributes)
    {
        glDisableVertexAttribArray(attribute);
    }

    _attributes.clear();

    CHECK_GL_ERRORS
}

void Material::setAttribute(const QString & name, const ArrayBuffer & attribute)
{
    CLEAR_GL_ERRORS

    const GLuint ATTRIB_LOCATION = _program.getAttribLocation(name.toStdString().c_str());
    glEnableVertexAttribArray(ATTRIB_LOCATION);
    glBindBuffer(GL_ARRAY_BUFFER, attribute.id());
    glVertexAttribPointer(ATTRIB_LOCATION, 
                          attribute.nbComponentsPerItem(), 
                          attribute.type(), 
                          GL_FALSE, // normalized ??? for colors
                          0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    CHECK_GL_ERRORS

    _attributes.push_back(ATTRIB_LOCATION);
}

void Material::setAttributes(const Geometry & geometry)
{
    const QMap<QString, ArrayBuffer> attributes = geometry.attributes();
    for(const QString & name : attributes.keys())
    {
        const ArrayBuffer & buffer = attributes[name];
        setAttribute(name, buffer);
    }
}

void Material::setProgram(const GLSLProgramObject & program)
{
    _program = program;
}

void Material::setUniform(const QString & name, glm::mat4 matrix)
{
    _program.setUniformMatrix("mvp_mat", glm::value_ptr(matrix), 4);
}

void Material::addTexture(const Texture2D & texture)
{
    _textures.push_back(texture);
}

void Material::enableTextures()
{
    CLEAR_GL_ERRORS

    if(!_textures.empty())
    {
        glEnable(GL_TEXTURE_2D);
    }

    int texture_unit = GL_TEXTURE0;
    for(const Texture2D & texture : _textures)
    {
        glActiveTexture(texture_unit);
        glBindTexture(GL_TEXTURE_2D, texture.id());
        ++texture_unit;
    }

    CHECK_GL_ERRORS
}

void Material::disableTextures()
{
    CLEAR_GL_ERRORS

    glDisable(GL_TEXTURE_2D);

    int texture_unit = GL_TEXTURE0;
    for(const Texture2D & texture : _textures)
    {
        glActiveTexture(texture_unit);
        glBindTexture(GL_TEXTURE_2D, 0);
        ++texture_unit;
    }

    CHECK_GL_ERRORS
}

void Material::clean()
{
    _textures.clear();
}