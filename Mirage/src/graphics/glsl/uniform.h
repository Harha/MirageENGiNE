#ifndef UNIFORM_H
#define UNIFORM_H

// std includes
#include <string>

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

		GLSLUniform(
			const std::string & name = "NULL",
			GLenum type = 0,
			GLint size = 0,
			GLint location = 0
		) :
			name(name),
			type(type),
			size(size),
			location(location)
		{

		}

	};

}

#endif // UNIFORM_H