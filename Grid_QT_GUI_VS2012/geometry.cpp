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

void Geometry::setStreamAttribute(const QString & name, const StreamArrayBuffer & buffer)
{
    _stream_attributes[name] = buffer;
    //_attributes[name] = _stream_attributes[name];
}

void Geometry::setStaticAttribute(const QString & name, const StaticArrayBuffer & buffer)
{
    _static_attributes[name] = buffer;
    //_attributes[name] = _static_attributes[name];
}

void Geometry::clean()
{
    _static_attributes.clear();
    _stream_attributes.clear();
    //_attributes.clear();
}

const QMap<QString, StreamArrayBuffer> & Geometry::streamAttributes() const
{
    return _stream_attributes;
}

const QMap<QString, StaticArrayBuffer> & Geometry::staticAttributes() const
{
    return _static_attributes;
}
/*
const QMap<QString, ArrayBuffer &> & Geometry::attributes() const
{
    //return _attributes;
}*/

unsigned int Geometry::nbELements() const
{
    return _elements.nbElements();
}

unsigned int Geometry::nbVertices() const
{
    //if(!_attributes.empty())
      //  return _attributes.first().nbItems();

    return 0;
}
