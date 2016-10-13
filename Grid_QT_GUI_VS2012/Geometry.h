#pragma once

#include "Buffer.h"
#include <QMap>
#include <QString>
#include <memory>

//-----------------------------------------------------------------------------
class Geometry
{
public:
    bool hasElements() const;
    unsigned int nbELements() const;
    unsigned int nbVertices() const;

    const std::shared_ptr<ElementArrayBuffer> elements() const;
    const QMap<QString, std::shared_ptr<ArrayBuffer>> & Geometry::attributes() const;

    void setElements(const std::shared_ptr<ElementArrayBuffer> & elements);
    void addAttribute(const QString & name, const std::shared_ptr<ArrayBuffer> & buffer);
    void clean();

private:
    std::shared_ptr<ElementArrayBuffer> _elements;
    QMap<QString, std::shared_ptr<ArrayBuffer>> _attributes;
};