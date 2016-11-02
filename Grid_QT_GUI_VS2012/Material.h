#pragma once

#include "Buffer.h"
#include "Texture.h"
#include "Geometry.h"
#include "GLSLProgramObject.h"
#include "Camera.h"
#include "Light.h"
#include <QString>
#include <QColor>
#include <glm/glm.hpp>

class Material
{
protected:
    QVector<Texture2D> _textures;
    GLSLProgramObject _program;
    QVector<GLuint> _attributes;

    void enableTextures();
    void disableTextures();

    virtual void initGL() = 0;
    virtual void cleanupGL() = 0;

    // material must be enabled (bind program) prior to call these
    void setUniform(const QString & name, glm::mat4 & matrix);
    void setUniform(const QString & name, glm::vec4 & v);
    void setUniform(const QString & name, glm::vec3 & v);
    void setUniform(const QString & name, float & f);
    void setUniform(const QString & name, QColor & v);

public:
    virtual void enable();
    virtual void disable();
    void addTexture(const Texture2D & texture);
    void clean();

    // material must be enabled (bind program) prior to call these
    virtual void setUniforms(const Camera & camera, const QVector<Light> & lights) = 0;
    GLuint getAttributeLocation(const QString & name) const;
};