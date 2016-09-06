#pragma once

#include <GL/glew.h>

#include <QString>

class Texture2D
{
private:
    QString filename;
    GLuint id;
    int width;
    int height;

public:
    Texture2D(const QString & filename);
    virtual ~Texture2D();
    void reset();
};