#pragma once

#include <GL/glew.h>
#include <QString>
#include "SelfCleaned.h"

//-----------------------------------------------------------------------------
class Texture2D : public SelfCleaned
{
protected:
    GLuint _id;
    QString _filename;
    int _width;
    int _height;
    GLint _mag_filter;
    GLint _min_filter;
    GLint _wrap;
    bool _anisotropic;
    bool _mipmaps;

    virtual void clean();

public:
    Texture2D();
    Texture2D(const QString & filename);
    virtual ~Texture2D();
    GLuint id() const {return _id;}
    void setAnisotropic(bool val);
    void setFiltering(GLint filter);
    void setWrapping(GLint wrap);
    void setMipmaps(bool val); // This changes the minification filter
};