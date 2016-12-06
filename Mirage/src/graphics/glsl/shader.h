#ifndef SHADER_H
#define SHADER_H

// std includes
#include <iostream>
#include <string>
#include <map>

// mirage includes
#include "graphics/glsl/uniform.h"

typedef unsigned int GLuint;
typedef unsigned int GLenum;
typedef int GLsizei;

namespace mirage
{

	class TxtFile;

	class ShaderData
	{
	public:
		ShaderData();
		~ShaderData();
		void addReference();
		void delReference();
		void addUniform(GLSLUniform u);
		void delUniform(const std::string & name);
		const GLuint getProgram() const;
		std::map<std::string, GLSLUniform> getUniforms() const;
		const int32_t getRefAmount() const;
	private:
		GLuint m_program;
		std::map<std::string, GLSLUniform> m_uniforms;
		int32_t m_refAmount;
	};

	extern std::map<std::string, ShaderData *> LOADED_SHADERS;

	class ShaderProgram
	{
	public:
		ShaderProgram(
			const std::string & name,
			const std::string & filePathGeom,
			const std::string & filePathVert,
			const std::string & filePathFrag
		);
		~ShaderProgram();
		std::string preprocessShader(const TxtFile & src);
		void attachShader(const std::string & src, GLenum type);
		void linkProgram();
		void validateProgram();
		void gatherActiveUniforms();
		std::string getShaderInfoLog(GLuint handle) const;
		std::string getProgramInfoLog() const;
	private:
		std::string m_name;
		std::string m_filePathGeom;
		std::string m_filePathVert;
		std::string m_filePathFrag;
		ShaderData * m_data;
	};

}

#endif // SHADER_H