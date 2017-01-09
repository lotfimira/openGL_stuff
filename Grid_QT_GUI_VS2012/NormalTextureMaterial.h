#pragma once

#include "Material.h"
#include <QColor>

//-----------------------------------------------------------------------------
// A material to vizualize normals stored in a texture
class NormalTextureMaterial : public Material
{
protected:
    float _normal_length;
    QColor _color;
    StreamTexture2D _normal_texture;

    virtual void initGL();
    virtual void cleanupGL();

public:
    NormalTextureMaterial();
    virtual void setUniforms(const Camera & camera, 
                             const QVector<Light> & lights);

    void setColor(const QColor &);
    void setNormalLength(float);
    void setNormals(const QVector<glm::vec3> & normals, int width, int height);
};

