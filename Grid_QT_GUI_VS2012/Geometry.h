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
    const QMap<QString, ArrayBufferPtr> & attributes() const;

    void setElements(const ElementArrayBuffer & elements);
    void setAttribute(const QString & name, ArrayBufferPtr buffer);
    void clean();

private:
    ElementArrayBuffer _elements;
    QMap<QString, ArrayBufferPtr> _attributes;
};