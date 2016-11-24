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
    const QMap<QString, StreamArrayBuffer> & streamAttributes() const;
    const QMap<QString, StaticArrayBuffer> & staticAttributes() const;
    const QMap<QString, ArrayBuffer> & attributes() const;

    void setElements(const ElementArrayBuffer & elements);
    void setStaticAttribute(const QString & name, const StaticArrayBuffer & buffer);
    void setStreamAttribute(const QString & name, const StreamArrayBuffer & buffer);
    void clean();

private:
    ElementArrayBuffer _elements;
    QMap<QString, StaticArrayBuffer> _static_attributes; // copies owned
    QMap<QString, StreamArrayBuffer> _stream_attributes; // copies owned
    QMap<QString, ArrayBuffer> _attributes; // copies of the copies
};