#pragma once

#include <GL/glew.h>
#include <QString>
#include "SelfCleaned.h"
#include <glm/glm.hpp>

//-----------------------------------------------------------------------------
class Texture2D : public SelfCleaned
{
public:

    enum Type
    {
        UByte = GL_UNSIGNED_BYTE,
        Float = GL_FLOAT
    };

    enum Format
    {
        RGBA = GL_RGBA,
        RGB = GL_RGB
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

private:
    void initialize(void * data);

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
    GLenum _type;
    GLint _format;

    virtual void clean();
    GLint getMipmapFilter(Filter f);

public:
    Texture2D();
    Texture2D(const QString & filename);
    Texture2D(int width, int height, const QVector<glm::vec3> &);
    Texture2D(int width, int height, const QVector<glm::u8vec4> &);
    Texture2D(int width, int height, Type type = UByte, Format format = RGBA);
    virtual ~Texture2D();
    GLuint id() const {return _id;}
    void setAnisotropic(bool val);
    void setFiltering(Filter val);
    void setWrapping(Wrap wrap);
    void setMipmaps(bool val); // This changes the minification filter
    int width() { return _width; }
    int height() { return _height; }
};

class StreamTexture2D : public Texture2D
{
public:
    StreamTexture2D();
    StreamTexture2D(int width, int height, const QVector<glm::vec3> &);
    StreamTexture2D(int width, int height, Type type = UByte, Format format = RGBA);
    void update(const QVector<glm::vec3> &, int width, int height);
};