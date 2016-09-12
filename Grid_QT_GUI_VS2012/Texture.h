#pragma once

#include <GL/glew.h>

#include <QString>

class Texture2D
{
private:
    QString _filename;
    GLuint _id;
    int _width;
    int _height;

    GLint _filter;
    GLint _wrap;

    bool _anisotropic;

public:
    Texture2D();
    virtual ~Texture2D();

    void clean();
    void load(const QString & filename);

    GLuint id() {return _id;}

    void setAnisotropic(bool val);
};