#include "Texture.h"
#include <QImage>
#include <QFileInfo>
#include <QGLWidget>

Texture2D::Texture2D() : _filename(""), _width(0), _height(0), _id(0), 
                         _filter(GL_LINEAR)
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

    glEnable(GL_TEXTURE_2D); // Enable texturing

    glGenTextures(1, &_id); // Obtain an id for the texture
    glBindTexture(GL_TEXTURE_2D, _id); // Set as the current texture

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    QImage im(filename);
    QImage tex = QGLWidget::convertToGLFormat(im);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.width(), tex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filter);

    glDisable(GL_TEXTURE_2D);

    _filename = filename;
    _width = tex.width();
    _height = tex.height();
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