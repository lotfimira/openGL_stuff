#pragma once

#include "Material.h"
#include <QColor>

class StandardMaterial : public Material
{
protected:
    bool _two_sided_lighting;
    GLfloat _shininess;
    GLfloat _shine_intensity;
    QColor _color;

    virtual void initGL();
    virtual void cleanupGL();

public:
    StandardMaterial();
    virtual void setUniforms(const Camera & camera, const QVector<Light> & lights);

    void setColor(const QColor &);
};