#include "ShaderManager.h"


//-----------------------------------------------------------------------------
QMap<QString, GLSLProgramObject> ShaderManager::_shaders;


void ShaderManager::addShader(const QString & name, 
                              const GLSLProgramObject & program)
{
    _shaders[name] = program;
}

GLSLProgramObject ShaderManager::getShader(const QString & name)
{
    if(_shaders.contains(name))
        return _shaders[name];
    else
    {
        printf("WARNING: unknown shader %s\n", name.toStdString().c_str());
        return GLSLProgramObject();
    }
}

bool ShaderManager::hasShader(const QString & name)
{
    return _shaders.contains(name);
}