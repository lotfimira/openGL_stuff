#include "Geometry.h"

bool Geometry::hasElements() const
{
    if(_elements)
        return _elements->isValid();
    else
        return false;
}

const std::shared_ptr<ElementArrayBuffer> Geometry::elements() const
{
    return _elements;
}

void Geometry::setElements(const std::shared_ptr<ElementArrayBuffer> & elements)
{
    _elements = elements;
}

void Geometry::addAttribute(const QString & name, const std::shared_ptr<ArrayBuffer> & buffer)
{
    if(!buffer)
        throw std::invalid_argument( "addAttribute: NULL buffer" );

    _attributes[name] = buffer;
}

void Geometry::clean()
{
    _attributes.clear();
}

const QMap<QString, std::shared_ptr<ArrayBuffer>> & Geometry::attributes() const
{
    return _attributes;
}

unsigned int Geometry::nbELements() const
{
    if(_elements && _elements->isValid())
    {
        return _elements->nbElements();
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
        return _attributes.first()->nbItems();
}
