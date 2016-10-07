#pragma once

#include "Buffer.h"
#include "Texture.h"
#include "GLSLProgramObject.h"
#include <QString>
#include <glm/glm.hpp>

class Material
{
protected:
    QVector<Texture2D> _textures;
    GLSLProgramObject _program;

    void enableTextures();
    void disableTextures();

public:
    void enable();
    void disable();
    void setAttribute(const QString & name, const ArrayBuffer & attribute);
    void setUniform(const QString & name, glm::mat4 matrix);
    void setProgram(const GLSLProgramObject & program);
    void addTexture(const Texture2D & texture);
    void clean();
};