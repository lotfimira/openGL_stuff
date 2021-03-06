//
// GLSLProgramObject.h - Wrapper for GLSL program objects
//
// Author: Louis Bavoil
// Email: sdkfeedback@nvidia.com
//
// Copyright (c) NVIDIA Corporation. All rights reserved.
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <vector>

class GLSLProgramObject
{
public:
	GLSLProgramObject();
	virtual ~GLSLProgramObject();

	void destroy();

	void bind();

	void unbind();

	void setUniform(std::string name, GLfloat* val, int count);
    void setUniform(std::string name, GLint* val, int count);
    void setUniform(std::string name, GLuint* val, int count);
    void setUniform(std::string name, bool val);
    void setUniformMatrix(std::string name, GLfloat *val, int count);

	void setTextureUnit(std::string texname, int texunit);
    void setTextureUnitEnum(std::string texname, int texunit_enum);

	void bindTexture(GLenum target, std::string texname, GLuint texid, int texunit);

	void bindTexture2D(std::string texname, GLuint texid, int texunit) {
		bindTexture(GL_TEXTURE_2D, texname, texid, texunit);
	}

	void bindTexture3D(std::string texname, GLuint texid, int texunit) {
		bindTexture(GL_TEXTURE_3D, texname, texid, texunit);
	}

	void bindTextureRECT(std::string texname, GLuint texid, int texunit) {
		bindTexture(GL_TEXTURE_RECTANGLE_ARB, texname, texid, texunit);
	}

	bool attachVertexShader(std::string filename);

	bool attachFragmentShader(std::string filename);

    bool attachGeometryShader(std::string filename);

	virtual bool link();

	inline GLuint getProgId() { return _progId; }
	
    GLuint getAttribLocation(const char * attrib_name) const;

protected:
	std::vector<GLuint>		_vertexShaders;
	std::vector<GLuint>		_fragmentShaders;
    std::vector<GLuint>		_geometryShaders;
	GLuint					_progId;
};

