#pragma once

#include "Material.h"
#include <QColor>

//-----------------------------------------------------------------------------
// A material to vizualize normals
class NormalMaterial : public Material
{
protected:
    float _normal_length;
    QColor _color;

    virtual void initGL();
    virtual void cleanupGL();

public:
    NormalMaterial();
    virtual void setUniforms(const Camera & camera, 
                             const QVector<Light> & lights);

    void setColor(const QColor &);
    void setNormalLength(float);
};

