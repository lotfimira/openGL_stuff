#include "MeshList.h"
#include <GL/glew.h>

MeshList * MeshList::_instance = 0;

MeshList * MeshList::instance()
{
    if(!_instance)
        _instance = new MeshList();

    return _instance;
}

void drawBlueQuad()
{
    // no lighting
    glDisable(GL_LIGHTING);

    // blue
    glColor4f(0, 0, 1, 1);

    // quad facing the camera
    int s = 1;
    int z = 0;
    glBegin(GL_QUADS);
    glVertex3f(-s, -s, z);
    glVertex3f(s, -s, z);
    glVertex3f(s, s, z);
    glVertex3f(-s, s, z);
    glEnd();
}

void MeshList::draw(const Camera & camera, const QVector<Light> & lights)
{
    for(Mesh * mesh : _meshes)
    {
        mesh->draw(camera, lights);
    }
}

void MeshList::animate()
{
    for(Mesh * mesh : _meshes)
    {
        mesh->animate();
    }
}

void MeshList::addMesh(Mesh * mesh)
{
    _meshes.push_back(mesh);
}

void MeshList::clean()
{
    for(Mesh * mesh : _meshes)
    {
        delete mesh;
    }

    _meshes.clear();
}