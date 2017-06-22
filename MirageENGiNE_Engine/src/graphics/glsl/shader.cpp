#include "shader.h"

#pragma warning(disable : 4307)

// std includes
#include <vector>
#include <regex>
#include <exception>
#include <stdexcept>

// lib includes
#include "3rdparty/glad/glad.h"

// mirage includes
#include "config.h"
#include "macros.h"
#include "util/strutil.h"
#include "util/txtfile.h"

namespace mirage
{

	// ---------------------------------------------------------------------------
	// ShaderData
	// ---------------------------------------------------------------------------

	ShaderData::ShaderData() :
		m_program(0),
		m_uniforms(),
		m_refAmount(0)
	{
		m_program = glCreateProgram();

		MLOG_DEBUG("ShaderData::ShaderData, initialized. Program: %d", m_program);
	}

	ShaderData::~ShaderData()
	{
		glDeleteProgram(m_program);

		MLOG_DEBUG("ShaderData::~ShaderData, destroyed.");
	}

	const GLuint ShaderData::getProgram() const
	{
		return m_program;
	}

	void ShaderData::addUniform(GLSLUniform u)
	{
		m_uniforms[u.name] = u;
	}

	void ShaderData::delUniform(const std::string & name)
	{
		m_uniforms.erase(name);
	}

	std::map<std::string, GLSLUniform> ShaderData::getUniforms() const
	{
		return m_uniforms;
	}

	void ShaderData::addReference()
	{
		m_refAmount++;
	}

	void ShaderData::delReference()
	{
		m_refAmount = (m_refAmount - 1 < 0) ? 0 : m_refAmount - 1;
	}

	const int32_t ShaderData::getRefAmount() const
	{
		return m_refAmount;
	}

	// ---------------------------------------------------------------------------
	// ShaderProgram
	// ---------------------------------------------------------------------------

	std::map<std::string, ShaderData *> LOADED_SHADERS;

	ShaderProgram::ShaderProgram(
		const std::string & name,
		const std::string & filePathGeom,
		const std::string & filePathVert,
		const std::string & filePathFrag
	) :
		m_name(name),
		m_filePathGeom(filePathGeom),
		m_filePathVert(filePathVert),
		m_filePathFrag(filePathFrag),
		m_data(nullptr)
	{
		ShaderData * data = LOADED_SHADERS[m_name];

		// This is a new shader program
		if (data == nullptr)
		{
			m_data = new ShaderData();
			m_data->addReference();
			LOADED_SHADERS[m_name] = m_data;

			// Load the shaders into memory
			TxtFile * txtFileGeom = nullptr, *txtFileVert = nullptr, *txtFileFrag = nullptr;
			if (!m_filePathGeom.empty()) txtFileGeom = new TxtFile("./data/shaders/" + m_filePathGeom);
			if (!m_filePathVert.empty()) txtFileVert = new TxtFile("./data/shaders/" + m_filePathVert);
			if (!m_filePathFrag.empty()) txtFileFrag = new TxtFile("./data/shaders/" + m_filePathFrag);

			// Preprocess and extract each shader into string
			std::string txtSrcGeom, txtSrcVert, txtSrcFrag;
			if (txtFileGeom != nullptr) txtSrcGeom = preprocessShader(*txtFileGeom);
			if (txtFileVert != nullptr) txtSrcVert = preprocessShader(*txtFileVert);
			if (txtFileFrag != nullptr) txtSrcFrag = preprocessShader(*txtFileFrag);

			// Compile and attach each shader into the program
			if (!txtSrcGeom.empty()) attachShader(txtSrcGeom, GL_GEOMETRY_SHADER);
			if (!txtSrcVert.empty()) attachShader(txtSrcVert, GL_VERTEX_SHADER);
			if (!txtSrcFrag.empty()) attachShader(txtSrcFrag, GL_FRAGMENT_SHADER);

			// Link, validate the program and gather active uniforms
			linkProgram();
			validateProgram();
			gatherActiveUniforms();

			// Clean up heap allocated data
			MDELETES(txtFileGeom);
			MDELETES(txtFileVert);
			MDELETES(txtFileFrag);
		}
		// This is an existing shader program
		else
		{
			m_data = data;
			m_data->addReference();
		}

		MLOG_DEBUG("ShaderProgram::ShaderProgram created. Name: %s, reference amount: %d", m_name.c_str(), m_data->getRefAmount());
	}

	ShaderProgram::~ShaderProgram()
	{
		m_data->delReference();

		if (m_data->getRefAmount() <= 0)
		{
			LOADED_SHADERS.erase(m_name);
			MDELETES(m_data);

			MLOG_DEBUG("ShaderProgram::~ShaderProgram, destroying program. Name: %s", m_name.c_str());
		}
	}

	void ShaderProgram::bind()
	{
		glUseProgram(m_data->getProgram());
	}

	std::string ShaderProgram::preprocessShader(const TxtFile & src)
	{
		std::vector<std::string> shader_src = src.getLines();
		std::string shader_out = "";

		for (auto l : shader_src)
		{
			// Trim any leading/trailing/extra ws
			l.erase(std::unique(l.begin(), l.end(), istwospace), l.end());

			// Handle directives and so on...
			switch (cstr2int(l.substr(0U, 8U).c_str()))
			{
			case cstr2int("#include"):
			{
				shader_out += preprocessShader(TxtFile("./data/shaders/" + l.substr(10U, l.size() - 11)));
			} break;
			default:
			{
				shader_out += l + "\n";
			} break;
			}
		}

		return shader_out;
	}

	void ShaderProgram::attachShader(const std::string & src, GLenum type)
	{
		// Create the shader with specified type
		GLuint handle = glCreateShader(type);

		if (handle == NULL)
		{
			throw std::runtime_error("Shader::attachShader, error. glCreateShader returned NULL.");
		}

		// Convert source to c-string
		const char * src_data = src.c_str();

		// Compile the shader
		glShaderSource(handle, 1, &src_data, NULL);
		glCompileShader(handle);

		// Get compile status
		GLint status;
		glGetShaderiv(handle, GL_COMPILE_STATUS, &status);

		if (status == NULL)
		{
			throw std::runtime_error(std::string("Shader::attachShader, error. glCompileShader failed. Info log:\n\n" + getShaderInfoLog(handle)).c_str());
		}

		// Attach the shader to program
		glAttachShader(m_data->getProgram(), handle);

		MLOG_DEBUG("ShaderProgram::attachShader, success. Shader compiled and attached to program successfully. Type: %zu, name: %s", type, m_name.c_str());
	}

	void ShaderProgram::linkProgram()
	{
		// Link the program
		glLinkProgram(m_data->getProgram());

		// Get link status
		GLint status;
		glGetProgramiv(m_data->getProgram(), GL_LINK_STATUS, &status);

		if (status == NULL)
		{
			throw std::runtime_error(std::string("Shader::linkProgram, error. glLinkProgram failed. Info log:\n\n" + getProgramInfoLog()).c_str());
		}

		MLOG_DEBUG("ShaderProgram::linkProgram, success. Program linked successfully. Name: %s", m_name.c_str());
	}

	void ShaderProgram::validateProgram()
	{
		// Validate the program
		glValidateProgram(m_data->getProgram());

		// Get validation status
		GLint status;
		glGetProgramiv(m_data->getProgram(), GL_VALIDATE_STATUS, &status);

		if (status == NULL)
		{
			throw std::runtime_error(std::string("Shader::validateProgram, error. glValidateProgram failed. Info log:\n\n" + getProgramInfoLog()).c_str());
		}

		MLOG_DEBUG("ShaderProgram::validateProgram, success. Program validated successfully. Name: %s", m_name.c_str());
	}

	void ShaderProgram::gatherActiveUniforms()
	{
		// Get uniform count
		GLint uniforms_num;
		glGetProgramiv(m_data->getProgram(), GL_ACTIVE_UNIFORMS, &uniforms_num);

		// Gather all uniforms from the program
		for (GLint i = 0; i < uniforms_num; i++)
		{
			// Uniform data temp storage
			GLchar u_name[255];
			GLenum u_type;
			GLint u_size;
			GLint u_location;

			// Get uniform information
			glGetActiveUniform(m_data->getProgram(), i, sizeof(u_name) - 1, NULL, &u_size, &u_type, u_name);
			u_location = glGetUniformLocation(m_data->getProgram(), u_name);

			if (u_location == -1)
			{
				throw std::runtime_error("Shader::gatherActiveUniforms, error. glGetUniformLocation failed.");
			}

			// Create the uniform object & save it
			GLSLUniform uniform{ std::string(u_name), u_type, u_size, u_location };
			m_data->addUniform(uniform);

			MLOG_DEBUG("ShaderProgram::gatherActiveUniforms, addUniform. Name: %s, type: %u, size: %d, location: %d", u_name, u_type, u_size, u_location);
		}

		MLOG_DEBUG("ShaderProgram::gatherActiveUniforms, success. Program uniforms gathered successfully. Name: %s, active uniform count: %zd", m_name.c_str(), m_data->getUniforms().size());
	}

	void ShaderProgram::setUniformBool(const std::string & name, GLint b)
	{
		glUniform1i(m_data->getUniforms()[name].location, b);
	}

	void ShaderProgram::setUniformInt(const std::string & name, GLint i)
	{
		glUniform1i(m_data->getUniforms()[name].location, i);
	}

	void ShaderProgram::setUniformFloat(const std::string & name, GLfloat f)
	{
		glUniform1f(m_data->getUniforms()[name].location, f);
	}

	void ShaderProgram::setUniformVec3(const std::string & name, const glm::vec3 & v)
	{
		glUniform3f(m_data->getUniforms()[name].location, v.x, v.y, v.z);
	}

	void ShaderProgram::setUniformVec4(const std::string & name, const glm::vec4 & v)
	{
		glUniform4f(m_data->getUniforms()[name].location, v.x, v.y, v.z, v.w);
	}

	void ShaderProgram::setUniformMat4(const std::string & name, const glm::mat4 & m)
	{
		glUniformMatrix4fv(m_data->getUniforms()[name].location, 1, GL_FALSE, &m[0][0]);
	}

	std::string ShaderProgram::getShaderInfoLog(GLuint handle) const
	{
		GLint infolog_len;
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infolog_len);
		GLchar * infolog_str = new GLchar[infolog_len];
		glGetShaderInfoLog(handle, infolog_len, NULL, infolog_str);
		return std::string(infolog_str);
	}

	std::string ShaderProgram::getProgramInfoLog() const
	{
		GLint infolog_len;
		glGetProgramiv(m_data->getProgram(), GL_INFO_LOG_LENGTH, &infolog_len);
		GLchar * infolog_str = new GLchar[infolog_len];
		glGetProgramInfoLog(m_data->getProgram(), infolog_len, NULL, infolog_str);
		return std::string(infolog_str);
	}


}