#include "Texture.h"
#include "GlUtils.h"
#include <QImage>
#include <QFileInfo>
#include <QGLWidget>

Texture2D::Texture2D() : _filename(""), _width(0), _height(0), _id(0), 
                         _filter(GL_LINEAR), _wrap(GL_REPEAT)
{

}

Texture2D::~Texture2D()
{
    clean();
}

void Texture2D::load(const QString & filename)
{
    //glActiveTexture(GL_TEXTURE0);

    clean();

    QFileInfo file_info(filename);
    if(!file_info.exists())
    {
        printf("File not found %s\n", filename.toStdString().c_str());
        return;
    }

    QImage image(filename);
    image = image.convertToFormat(QImage::Format_RGBA8888);

    uchar * bits = image.bits();
    for(int i = 0; i < 128; ++i)
    {
        printf("%d ", bits[i]);
    }

    GLuint id;
    glGenTextures(1, &id); // ??  why can't i use _id member directly here
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filter);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());

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