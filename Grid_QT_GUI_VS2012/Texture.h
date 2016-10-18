#pragma once

#include <GL/glew.h>
#include <QString>
#include <memory>

//-----------------------------------------------------------------------------
class TextureAutoCleaner
{
private:
    GLuint _id;

public:
    TextureAutoCleaner() : _id(0) {}
    TextureAutoCleaner(GLuint id) : _id(id) {}
    ~TextureAutoCleaner()
    {
        GLuint texture_id = _id;
        if(glIsTexture(texture_id))
        {
            glDeleteTextures(1, &texture_id);
        }
    }
};

//-----------------------------------------------------------------------------
class Texture2D
{
protected:
    GLuint _id;
    std::shared_ptr<TextureAutoCleaner> _auto_clean;

    QString _filename;
    int _width;
    int _height;

    GLint _mag_filter;
    GLint _min_filter;
    GLint _wrap;

    bool _anisotropic;
    bool _mipmaps;

public:
    Texture2D();
    Texture2D(const QString & filename);
    virtual ~Texture2D();

    GLuint id() const {return _id;}

    void setAnisotropic(bool val);
    void setFiltering(GLint filter);
    void setWrapping(GLint wrap);

    /* This changes the minification filter */
    void setMipmaps(bool val);
};