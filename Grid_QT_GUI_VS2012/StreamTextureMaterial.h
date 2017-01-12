#pragma once

#include "Material.h"

//-----------------------------------------------------------------------------
// A material displaying a stream texture without lighting
class StreamTextureMaterial : public Material
{
protected:
    StreamTexture2D _normal_texture;

    virtual void initGL();
    virtual void cleanupGL();

public:
    StreamTextureMaterial();
    virtual void setUniforms(const Camera & camera, 
                             const QVector<Light> & lights);

    void setTexturePixels(const QVector<glm::vec3> & normals, int width, int height);
};

