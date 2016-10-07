#include "Geometry.h"

bool Geometry::hasElements() const
{
    return _elements.isValid();
}

const ElementArrayBuffer & Geometry::elements() const
{
    return _elements;
}

void Geometry::setElements(const ElementArrayBuffer & elements)
{
    if(_elements.isValid())
        _elements.clean();

    _elements = elements;
}

void Geometry::addAttribute(const QString & name, const ArrayBuffer & buffer)
{
    if(_attributes.contains(name))
        _attributes[name].clean();

    _attributes[name] = buffer;
}

void Geometry::clean()
{
    for(ArrayBuffer & attribute : _attributes)
    {
        attribute.clean();
    }

    _attributes.clear();
}

const QMap<QString, ArrayBuffer> & Geometry::attributes() const
{
    return _attributes;
}

unsigned int Geometry::nbELements() const
{
    if(_elements.isValid())
    {
        return _elements.nbElements();
    }
    else
    {
        return 0;
    }
}

unsigned int Geometry::nbVertices() const
{
    if(_attributes.empty())
        return 0;
    else
        return _attributes.first().nbItems();
}
