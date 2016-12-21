#pragma once

#include "Material.h"
#include <QColor>

class WireframeMaterial : public Material
{
private:
    QColor _color;

protected:
    virtual void initGL();
    virtual void cleanupGL();

public:
    WireframeMaterial();
    virtual void setUniforms(const Camera & camera, const QVector<Light> & lights);
    void setColor(const QColor & color);
};