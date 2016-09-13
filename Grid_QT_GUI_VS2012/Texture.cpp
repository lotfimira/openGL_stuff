#include "Texture.h"
#include "GlUtils.h"
#include <QImage>
#include <QFileInfo>
#include <QGLWidget>

Texture2D::Texture2D() : _filename(""), _width(0), _height(0), _id(0), 
                         _filter(GL_LINEAR), _wrap(GL_REPEAT), 
                         _anisotropic(false)
{

}

Texture2D::~Texture2D()
{
    clean();
}

void Texture2D::load(const QString & filename)
{
    clean();

    QFileInfo file_info(filename);
    if(!file_info.exists())
    {
        printf("File not found %s\n", filename.toStdString().c_str());
        return;
    }

    QImage image(filename);
    image = image.convertToFormat(QImage::Format_RGBA8888);

    GLuint id;
    glGenTextures(1, &id); // ??  why can't i use _id member directly here
    glBindTexture(GL_TEXTURE_2D, id);

    // wrap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrap);

    // filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filter);

    // anisotropic
    if(_anisotropic)
    {
        if(glewIsExtensionSupported("GL_EXT_texture_filter_anisotropic"))
        {
            GLfloat aniso;
            glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);
        }
        else
        {
            printf("WARNING: Anisotropic filtering not supported\n");
        }
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());

    glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
    glGenerateMipmap(GL_TEXTURE_2D);

    _id = id;
    _filename = filename;
    _width = image.width();
    _height = image.height();
}

void Texture2D::clean()
{
    if(glIsTexture(_id))
    {
        glDeleteTextures(1, &_id);
    }

    _id = 0;
    _width = 0;
    _height = 0;
    _filename = "";
}

void Texture2D::setAnisotropic(bool val)
{
    _anisotropic = val;
}