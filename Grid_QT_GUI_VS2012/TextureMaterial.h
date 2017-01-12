#pragma once

#include "Material.h"

//-----------------------------------------------------------------------------
// A material displaying a texture without lighting
class TextureMaterial : public Material
{
protected:
    Texture2D _normal_texture;

    virtual void initGL();
    virtual void cleanupGL();

public:
    TextureMaterial();
    virtual void setUniforms(const Camera & camera, 
                             const QVector<Light> & lights);

    void setTexture(const Texture2DPtr);
};

