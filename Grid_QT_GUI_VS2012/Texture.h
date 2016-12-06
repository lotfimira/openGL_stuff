#pragma once

#include <GL/glew.h>
#include <QString>
#include "SelfCleaned.h"

//-----------------------------------------------------------------------------
class Texture2D : public SelfCleaned
{
public:

    enum Type
    {
        UByte = GL_UNSIGNED_BYTE,
        Float = GL_FLOAT
    };

    enum Filter
    {
        Nearest = GL_NEAREST,
        Linear = GL_LINEAR,
    };

    enum Wrap
    {
        Repeat = GL_REPEAT,
        Clamp = GL_CLAMP,
        ClampToEdge = GL_CLAMP_TO_EDGE,
    };

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
    GLint getMipmapFilter(Filter f);

public:
    Texture2D();
    Texture2D(const QString & filename);
    Texture2D(int width, int height, Type type = UByte);
    virtual ~Texture2D();
    GLuint id() const {return _id;}
    void setAnisotropic(bool val);
    void setFiltering(Filter val);
    void setWrapping(Wrap wrap);
    void setMipmaps(bool val); // This changes the minification filter
};