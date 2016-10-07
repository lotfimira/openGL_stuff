#include "Material.h"
#include "GlUtils.h"

void Material::enable()
{
    if(!_textures.isEmpty())
        enableTextures();

    _program.bind();
}

void Material::disable()
{
    disableTextures();
}

void Material::setAttribute(const QString & name, const ArrayBuffer & attribute)
{
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
}

void Material::setProgram(const GLSLProgramObject & program)
{
    _program = program;
}

void Material::setUniform(const QString & name, glm::mat4 matrix)
{
    _program.setUniformMatrix("mvp_mat", glm::value_ptr(mvp), 4);
}

void Material::addTexture(const Texture2D & texture)
{
    _textures.push_back(texture);
}

void Material::enableTextures()
{
    if(!_textures.empty())
    {
        glEnable(GL_TEXTURE_2D);
    }

    int texture_unit = 0;
    for(const Texture2D & texture : _textures)
    {
        glActiveTexture(texture_unit);
        glBindTexture(GL_TEXTURE_2D, texture.id());
        ++texture_unit;
    }
}

void Material::disableTextures()
{
    glDisable(GL_TEXTURE_2D);

    int texture_unit = 0;
    for(const Texture2D & texture : _textures)
    {
        glActiveTexture(texture_unit);
        glBindTexture(GL_TEXTURE_2D, 0);
        ++texture_unit;
    }
}

void Material::clean()
{
    for(Texture2D & texture : _textures)
    {
        texture.clean();
    }

    _textures.clear();
}