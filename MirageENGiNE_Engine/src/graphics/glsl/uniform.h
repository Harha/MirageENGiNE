#ifndef UNIFORM_H
#define UNIFORM_H

// std includes
#include <string>

// mirage includes
#include "macros.h"

typedef unsigned int GLuint;
typedef unsigned int GLenum;
typedef int GLint;
typedef int GLsizei;
typedef char GLchar;

namespace mirage
{

	struct GLSLUniform
	{
		std::string name;
		GLenum type;
		GLint size;
		GLint location;
	};

}

#endif // UNIFORM_H