//
// GLSLProgramObject.cpp - Wrapper for GLSL program objects
//
// Author: Louis Bavoil
// Email: sdkfeedback@nvidia.com
//
// Copyright (c) NVIDIA Corporation. All rights reserved.
////////////////////////////////////////////////////////////////////////////////

#define NV_REPORT_COMPILE_ERRORS
//#define NV_REPORT_UNIFORM_ERRORS

#include "GLSLProgramObject.h"
#include "nvShaderUtils.h"
#include "nvSDKPath.h"

static nv::SDKPath sdkPath;

GLSLProgramObject::GLSLProgramObject() :
	_progId(0)
{
}

GLSLProgramObject::~GLSLProgramObject()
{
}

void GLSLProgramObject::destroy()
{
	for (unsigned i = 0; i < _vertexShaders.size(); i++) {
		glDeleteShader(_vertexShaders[i]);
	}
	for (unsigned i = 0; i < _fragmentShaders.size(); i++) {
		glDeleteShader(_fragmentShaders[i]);
	}
	for (unsigned i = 0; i < _geometryShaders.size(); i++) {
		glDeleteShader(_geometryShaders[i]);
	}
	if (_progId != 0) {
		glDeleteProgram(_progId);
	}
}

bool GLSLProgramObject::attachVertexShader(std::string filename)
{
        GLuint shaderId = nv::CompileGLSLShaderFromFile(GL_VERTEX_SHADER, filename.c_str());
        if (shaderId == 0) {
            printf("Error: Vertex shader %s failed to compile\n", filename.c_str());
        }
        else {
            _vertexShaders.push_back(shaderId);
        }

        return shaderId > 0;
}

bool GLSLProgramObject::attachFragmentShader(std::string filename)
{
        GLuint shaderId = nv::CompileGLSLShaderFromFile(GL_FRAGMENT_SHADER, filename.c_str());
        if (shaderId == 0) {
            printf("Error: Fragment shader %s failed to compile\n", filename.c_str());
        }
        else {
            _fragmentShaders.push_back(shaderId);
        }

        return shaderId > 0;
}

bool GLSLProgramObject::attachGeometryShader(std::string filename)
{
        GLuint shaderId = nv::CompileGLSLShaderFromFile(GL_GEOMETRY_SHADER, filename.c_str());
        if (shaderId == 0) {
            printf("Error: Geometry shader %s failed to compile\n", filename.c_str());
        }
        else {
            _geometryShaders.push_back(shaderId);
        }

        return shaderId > 0;
}

bool GLSLProgramObject::link()
{
	_progId = glCreateProgram();

    for (unsigned i = 0; i < _vertexShaders.size(); i++) {
        glAttachShader(_progId, _vertexShaders[i]);
    }

    for (unsigned i = 0; i < _fragmentShaders.size(); i++) {
        glAttachShader(_progId, _fragmentShaders[i]);
    }

    for (unsigned i = 0; i < _geometryShaders.size(); i++) {
        glAttachShader(_progId, _geometryShaders[i]);
    }

    glLinkProgram(_progId);

    GLint success = 0;
    glGetProgramiv(_progId, GL_LINK_STATUS, &success);

    if (!success) {
        char temp[1024];
        glGetProgramInfoLog(_progId, 1024, NULL, temp);
        printf("Failed to link program: %s\n", temp);
    }

    return success;
}

void GLSLProgramObject::bind()
{
	glUseProgram(_progId);
}

void GLSLProgramObject::unbind()
{
	glUseProgram(0);
}

void GLSLProgramObject::setUniform(std::string name, GLfloat* val, int count)
{
	GLint id = glGetUniformLocation(_progId, name.c_str());
	if (id == -1) {
#ifdef NV_REPORT_UNIFORM_ERRORS
		std::cerr << m_vName << std::endl << m_fName << ":" << std::endl;
		std::cerr << "Warning: Invalid uniform parameter " << name << std::endl;
#endif
		return;
	}
	switch (count) {
		case 1:
			glUniform1fv(id, 1, val);
			break;
		case 2:
			glUniform2fv(id, 1, val);
			break;
		case 3:
			glUniform3fv(id, 1, val);
			break;
		case 4:
			glUniform4fv(id, 1, val);
			break;
	}
}

void GLSLProgramObject::setUniform(std::string name, GLint* val, int count)
{
	GLint id = glGetUniformLocation(_progId, name.c_str());
	if (id == -1) {
#ifdef NV_REPORT_UNIFORM_ERRORS
		std::cerr << m_vName << std::endl << m_fName << ":" << std::endl;
		std::cerr << "Warning: Invalid uniform parameter " << name << std::endl;
#endif
		return;
	}
	switch (count) {
		case 1:
			glUniform1iv(id, 1, val);
			break;
		case 2:
			glUniform2iv(id, 1, val);
			break;
		case 3:
			glUniform3iv(id, 1, val);
			break;
		case 4:
			glUniform4iv(id, 1, val);
			break;
	}
}

void GLSLProgramObject::setUniform(std::string name, GLuint* val, int count)
{
	GLuint id = glGetUniformLocation(_progId, name.c_str());
	if (id == -1) {
#ifdef NV_REPORT_UNIFORM_ERRORS
		std::cerr << m_vName << std::endl << m_fName << ":" << std::endl;
		std::cerr << "Warning: Invalid uniform parameter " << name << std::endl;
#endif
		return;
	}
	switch (count) {
		case 1:
			glUniform1uiv(id, 1, val);
			break;
		case 2:
			glUniform2uiv(id, 1, val);
			break;
		case 3:
			glUniform3uiv(id, 1, val);
			break;
		case 4:
			glUniform4uiv(id, 1, val);
			break;
	}
}


void GLSLProgramObject::setUniform(std::string name, bool val)
{
    setTextureUnit(name, val ? 1 : 0);
}

void GLSLProgramObject::setUniformMatrix(std::string name, GLfloat *val, int count)
{
    GLint id = glGetUniformLocation(_progId, name.c_str());
    if (id == -1) {
        #ifdef NV_REPORT_UNIFORM_ERRORS
        std::cerr << m_vName << std::endl << m_fName << ":" << std::endl;
        std::cerr << "Warning: Invalid uniform parameter " << name << std::endl;
        #endif
        return;
    }

    switch (count) {
        case 2:
            glUniformMatrix2fv(id, 1, GL_FALSE, val);
            break;
        case 3:
            glUniformMatrix3fv(id, 1, GL_FALSE, val);
            break;
        case 4:
            glUniformMatrix4fv(id, 1, GL_FALSE, val);
            break;
    }
}

void GLSLProgramObject::setTextureUnit(std::string texname, int texunit)
{
    if(texunit < 0 || texunit > 31)
    {
        printf("Error: setTextureUnit id must be within range [0, 31]");
    }

	GLint linked;
	glGetProgramiv(_progId, GL_LINK_STATUS, &linked);
	if (linked != GL_TRUE) {
        printf("Error: setTextureUnit needs program to be linked.\n");
	}
	GLint id = glGetUniformLocation(_progId, texname.c_str());
	if (id == -1) {
#ifdef NV_REPORT_UNIFORM_ERRORS
		std::cerr << "Warning: Invalid texture " << texname << std::endl;
#endif
		return;
	}
	glUniform1i(id, texunit);
}

void GLSLProgramObject::setTextureUnitEnum(std::string texname, int texunit_enum)
{
    if(texunit_enum < GL_TEXTURE0 || texunit_enum > GL_TEXTURE31)
    {
        printf("Error: setTextureUnitEnum id must be within range [GL_TEXTURE0, GL_TEXTURE31]");
    }

    setTextureUnit(texname, texunit_enum - GL_TEXTURE0);
}

void GLSLProgramObject::bindTexture(GLenum target, std::string texname, GLuint texid, int texunit)
{
	glActiveTexture(GL_TEXTURE0 + texunit);
	glBindTexture(target, texid);
	setTextureUnit(texname, texunit);
	glActiveTexture(GL_TEXTURE0);
}

GLuint GLSLProgramObject::getAttribLocation(const char * attrib_name)
{
    return glGetAttribLocation(_progId, attrib_name);
}
