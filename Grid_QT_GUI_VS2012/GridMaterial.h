#pragma once

#include "Material.h"

class GridMaterial : public Material
{
protected:
    virtual void initGL();
    virtual void cleanupGL();

public:
    GridMaterial();
    virtual void setUniforms(const Camera & camera, const QVector<Light> & lights);
};