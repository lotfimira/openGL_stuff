#pragma once

#include <QString>
#include <QMap>
#include <QVector>
#include <GLSLProgramObject.h>

//-----------------------------------------------------------------------------
class ShaderManager
{
private:
    static QMap<QString, GLSLProgramObject> _shaders;

public:

    static void addShader(const QString & name, const GLSLProgramObject & program);
    static bool hasShader (const QString & name);
    static GLSLProgramObject getShader(const QString & name);
};
