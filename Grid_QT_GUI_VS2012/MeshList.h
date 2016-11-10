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
    void draw(const Camera &);
    void addMesh(Mesh *);
    void clean();
    void animate();
};