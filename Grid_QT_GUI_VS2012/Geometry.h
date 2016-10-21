#pragma once

#include "Buffer.h"
#include <QMap>
#include <QString>

//-----------------------------------------------------------------------------
class Geometry
{
public:
    bool hasElements() const;
    unsigned int nbELements() const;
    unsigned int nbVertices() const;

    const ElementArrayBuffer elements() const;
    const QMap<QString, ArrayBuffer> & attributes() const;

    void setElements(const ElementArrayBuffer & elements);
    void addAttribute(const QString & name, const ArrayBuffer & buffer);
    void clean();

private:
    ElementArrayBuffer _elements;
    QMap<QString, ArrayBuffer> _attributes;
};