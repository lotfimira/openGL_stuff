#pragma once

#include "Mesh.h"
#include <QList>

class MeshList
{
private:
    static MeshList * _instance;
    QList<Mesh*> _meshes;

public:
    static MeshList * instance();
    void draw();
    void addMesh(Mesh *);
};