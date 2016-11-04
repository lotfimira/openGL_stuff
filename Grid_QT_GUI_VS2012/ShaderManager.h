#pragma once

#include <QString>
#include <QMap>
#include <GLSLProgramObject.h>

//-----------------------------------------------------------------------------
class ShaderManager
{
private:
    static ShaderManager * _instance;
    QMap<QString, GLSLProgramObject *> _shaders;

public:

    ShaderManager();
    ~ShaderManager();

    static ShaderManager * instance();

    bool addShader(const QString & name,
                   const QVector<QString> & vertex_shader_files,
                   const QVector<QString> & fragment_shader_files);

    GLSLProgramObject * getShader(const QString & name);
};
