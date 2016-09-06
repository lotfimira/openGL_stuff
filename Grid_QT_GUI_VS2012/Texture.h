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

public:
    Texture2D();
    virtual ~Texture2D();

    void clean();
    void load(const QString & filename);
};