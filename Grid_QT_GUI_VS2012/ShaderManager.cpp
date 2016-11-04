#include "ShaderManager.h"


//-----------------------------------------------------------------------------
ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
}

static ShaderManager * instance()
{

}

bool ShaderManager::addShader(const QString & name,
                              const QVector<QString> & vertex_shader_files,
                              const QVector<QString> & fragment_shader_files)
{

}

GLSLProgramObject * getShader(const QString & name)
{

}
