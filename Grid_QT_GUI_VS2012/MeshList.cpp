#include "MeshList.h"
#include <GL/glew.h>

MeshList * MeshList::_instance = 0;

MeshList * MeshList::instance()
{
    if(!_instance)
        _instance = new MeshList();

    return _instance;
}

void MeshList::draw(const Camera & camera)
{
    for(Mesh & mesh : *this)
    {
        mesh.draw(camera);
    }
}
