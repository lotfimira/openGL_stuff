#pragma once

#include "Texture.h"
#include <QString>

class Mesh
{
public:
    virtual void draw() = 0;
};

class GroundPlaneAnisotropic : public Mesh
{
private:
    //AnisoMaterial _material;
    Texture2D _texture2D;

public:
    GroundPlaneAnisotropic();
    ~GroundPlaneAnisotropic();
    void draw();
};