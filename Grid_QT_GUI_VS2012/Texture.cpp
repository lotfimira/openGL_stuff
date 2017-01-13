#include "Texture.h"
#include "GlUtils.h"
#include "MyException.h"
#include <QImage>
#include <QFileInfo>
#include <QGLWidget>

Texture2D::Texture2D() : 
    _filename(""), 
    _width(0), 
    _height(0), 
    _id(0), 
    _mag_filter(GL_LINEAR), 
    _min_filter(GL_LINEAR), 
    _wrap(GL_REPEAT), 
    _mipmaps(false), 
    _anisotropic(false),
    _type(GL_UNSIGNED_BYTE),
    _format(GL_RGBA)
{
}

Texture2D::~Texture2D()
{
    // checks reference counter, if last then call clean()
    autoClean();
}

Texture2D::Texture2D(const QString & filename) : 
    _mag_filter(GL_LINEAR),
    _min_filter(GL_LINEAR), 
    _wrap(GL_REPEAT), 
    _mipmaps(false), 
    _anisotropic(false),
    _type(UByte),
    _format(RGBA)
{
    QFileInfo file_info(filename);
    if(!file_info.exists())
    {
        printf("File not found %s\n", filename.toStdString().c_str());
        return;
    }

    QImage image(filename);
    if(!image.bits())
    {
        printf("Invalid image file %s\n", filename.toStdString().c_str());
        return;
    }

    // why QImage is always flipped vertically ?
    image = image.mirrored(false, true);
    image = image.convertToFormat(QImage::Format_RGBA8888);

    _filename = filename;
    _width = image.width();
    _height = image.height();

    initialize(image.bits());
}

Texture2D::Texture2D(int width, int height, Type type, Format format) : 
    _mag_filter(GL_LINEAR),
    _min_filter(GL_LINEAR), 
    _wrap(GL_REPEAT), 
    _mipmaps(false), 
    _anisotropic(false),
    _type(type),
    _format(format),
    _width(width),
    _height(height),
    _filename("")
{
    initialize(nullptr);
}

Texture2D::Texture2D(int width, int height, const QVector<glm::vec3> & data) : 
    _mag_filter(GL_LINEAR),
    _min_filter(GL_LINEAR), 
    _wrap(GL_REPEAT), 
    _mipmaps(false), 
    _anisotropic(false),
    _type(Float),
    _format(RGB),
    _width(width),
    _height(height),
    _filename("")
{
    if(width * height != data.size())
        throw new MyException("Texture2D::Texture2D() texture size and data do not match.");

    initialize((void *)data.data());
}

Texture2D::Texture2D(int width, int height, const QVector<glm::u8vec4> & data) : 
    _mag_filter(GL_LINEAR),
    _min_filter(GL_LINEAR), 
    _wrap(GL_REPEAT), 
    _mipmaps(false), 
    _anisotropic(false),
    _type(UByte),
    _format(RGBA),
    _width(width),
    _height(height),
    _filename("")
{
    if(width * height != data.size())
        throw new MyException("Texture2D::Texture2D() texture size and data do not match.");

    initialize((void *)data.data());
}

void Texture2D::initialize(void * data)
{
    CLEAR_GL_ERRORS

    GLuint id;
    glGenTextures(1, &id); // ??  why can't i use _id member directly here
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrap);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _mag_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _min_filter);

    glTexImage2D(GL_TEXTURE_2D, 0, _format, _width, _height, 0, _format, _type, data);

    glBindTexture(GL_TEXTURE_2D, 0);

    CHECK_GL_ERRORS

    _id = id;
}

void Texture2D::setAnisotropic(bool val)
{
    CLEAR_GL_ERRORS

    GLuint id = _id;
    if(!glIsTexture(id))
        return;

    _anisotropic = val;

    glBindTexture(GL_TEXTURE_2D, id);

    if(glewIsExtensionSupported("GL_EXT_texture_filter_anisotropic"))
    {
        if(_anisotropic)
        {
            GLfloat aniso;
            glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);
        }
        else
        {
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0.0f);
        }
    }
    else
    {
        if(_anisotropic)
        {
            printf("WARNING: Anisotropic filtering not supported\n");
        }
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    CHECK_GL_ERRORS
}

void Texture2D::setMipmaps(bool val)
{
    CLEAR_GL_ERRORS

    GLuint id = _id;
    if(!glIsTexture(id))
        return;

    _mipmaps = val;

    glBindTexture(GL_TEXTURE_2D, id);

    // generate mipmaps
    if(_mipmaps)
    {
        glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    // make sure the minification filter comply with the status of mipmaps
    if(_mipmaps)
    {
        if(_min_filter == GL_LINEAR)
        {
            _min_filter = GL_LINEAR_MIPMAP_LINEAR;
        }
        else if(_min_filter == GL_NEAREST)
        {
            _min_filter = GL_NEAREST_MIPMAP_NEAREST;
        }
    }
    else
    {
        if(_min_filter == GL_LINEAR_MIPMAP_LINEAR ||
           _min_filter == GL_LINEAR_MIPMAP_NEAREST)
        {
            _min_filter = GL_LINEAR;
        }
        else if(_min_filter == GL_NEAREST_MIPMAP_LINEAR ||
                _min_filter == GL_NEAREST_MIPMAP_NEAREST)
        {
            _min_filter = GL_NEAREST;
        }
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _min_filter);

    glBindTexture(GL_TEXTURE_2D, 0);

    CHECK_GL_ERRORS
}

GLint Texture2D::getMipmapFilter(Filter f)
{
    switch(f)
    {
        case Nearest : return GL_NEAREST_MIPMAP_NEAREST;
        case Linear  : return GL_LINEAR_MIPMAP_LINEAR;
    }

    throw new MyException("Texture2D::getMipmapFilter unknown filter typre");
}

void Texture2D::setFiltering(Filter val)
{
    CLEAR_GL_ERRORS

    GLuint id = _id;
    if(!glIsTexture(id))
        return;

    _min_filter = val;
    if(_mipmaps)
        _min_filter = getMipmapFilter(val);
    _mag_filter = val;

    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _mag_filter);
    glBindTexture(GL_TEXTURE_2D, 0);

    CHECK_GL_ERRORS
}

void Texture2D::setWrapping(Wrap wrap)
{
    CLEAR_GL_ERRORS

    GLuint id = _id;
    if(!glIsTexture(id))
        return;

    _wrap = wrap;

    glBindTexture(GL_TEXTURE_2D, id);

    // wrap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrap);

    glBindTexture(GL_TEXTURE_2D, 0);

    CHECK_GL_ERRORS
}

void Texture2D::clean()
{
    CLEAR_GL_ERRORS

    GLuint texture_id = _id;
    if(glIsTexture(texture_id))
    {
        glDeleteTextures(1, &texture_id);
        _id = 0;
    }

    CHECK_GL_ERRORS
}

//-----------------------------------------------------------------------------
StreamTexture2D::StreamTexture2D() : Texture2D()
{

}

StreamTexture2D::StreamTexture2D(int width, int height, 
                                 Type type, Format format) :
    Texture2D(width, height, type, format)
{

}

StreamTexture2D::StreamTexture2D(int width, int height, 
                                 const QVector<glm::vec3> & data) :
    Texture2D(width, height, data)
{

}

//-----------------------------------------------------------------------------
void StreamTexture2D::update(const QVector<glm::vec3> & vals, 
                             int width, int height)
{
    if(_type != Float)
        throw new MyException("StreamTexture2D::update incompatible type");

    if(_format != RGB)
        throw new MyException("StreamTexture2D::update incompatible format");

    if(width * height != vals.size())
        throw new MyException("StreamTexture2D::update [width, height] does not\
                              match array size");

    _width = width;
    _height = height;

    CLEAR_GL_ERRORS

    // TODO: use a Pixel Buffer Object to speed up update
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexImage2D(GL_TEXTURE_2D, 0, _format, _width, _height, 0, _format, _type, vals.data());
    glBindTexture(GL_TEXTURE_2D, 0);

    CHECK_GL_ERRORS
}