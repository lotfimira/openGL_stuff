#include "Geometry.h"

bool Geometry::hasElements() const
{
    return _elements.isValid();
}

const ElementArrayBuffer Geometry::elements() const
{
    return _elements;
}

void Geometry::setElements(const ElementArrayBuffer & elements)
{
    _elements = elements;
}

void Geometry::setAttribute(const QString & name, ArrayBufferPtr buffer)
{
    _attributes[name] = buffer;
}

void Geometry::clean()
{
    _attributes.clear();
}

const QMap<QString, ArrayBufferPtr> & Geometry::attributes() const
{
    return _attributes;
}

unsigned int Geometry::nbELements() const
{
    return _elements.nbElements();
}

unsigned int Geometry::nbVertices() const
{
    if(!_attributes.empty())
        return _attributes.first()->nbItems();

    return 0;
}
