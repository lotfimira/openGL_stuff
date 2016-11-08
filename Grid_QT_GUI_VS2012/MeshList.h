#pragma once

#include "Mesh.h"
#include <QVector>

class MeshList : public QVector<Mesh>
{
private:
    static MeshList * _instance;

public:
    static MeshList * instance();
    void draw(const Camera &);
};