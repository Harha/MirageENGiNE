#include "shader.h"

// std includes
#include <vector>
#include <regex>

// lib includes
#include "glad/glad.h"

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
		m_refAmount(0)
	{
		m_program = glCreateProgram();

		MLOG_INFO("ShaderData::ShaderData initialized successfully, program: %d", m_program);
	}

	ShaderData::~ShaderData()
	{
		glDeleteProgram(m_program);
	}

	void ShaderData::addReference()
	{
		m_refAmount++;
	}

	void ShaderData::delReference()
	{
		m_refAmount = (m_refAmount - 1 < 0) ? 0 : m_refAmount - 1;
	}

	const GLuint ShaderData::getProgram() const
	{
		return m_program;
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

			// Link and validate the program
			linkProgram();
			validateProgram();

			// TODO: Collect all active uniforms

		}
		// This is an existing shader program
		else
		{
			m_data = data;
			m_data->addReference();
		}

		MLOG_INFO("ShaderProgram::ShaderProgram initialized successfully. Name: %s, reference amount: %d", m_name.c_str(), m_data->getRefAmount());
	}

	ShaderProgram::~ShaderProgram()
	{
		m_data->delReference();

		if (m_data->getRefAmount() <= 0)
		{
			LOADED_SHADERS.erase(m_name);
			MDELETES(m_data);

			MLOG_INFO("ShaderProgram::~ShaderProgram, destroying program. Name: %s", m_name.c_str());
		}
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
		GLuint handle = glCreateShader(type);

		if (handle == NULL)
			throw std::exception("Shader::attachShader glCreateShader returned NULL.");

		const char * src_data = src.c_str();

		glShaderSource(handle, 1, &src_data, NULL);
		glCompileShader(handle);

		GLint status;
		glGetShaderiv(handle, GL_COMPILE_STATUS, &status);

		if (status == NULL)
			throw std::exception(std::string("Shader::attachShader glCompileShader failed. Info log:\n\n" + getShaderInfoLog(handle)).c_str());

		glAttachShader(m_data->getProgram(), handle);
	}

	void ShaderProgram::linkProgram()
	{
		glLinkProgram(m_data->getProgram());

		GLint status;
		glGetProgramiv(m_data->getProgram(), GL_LINK_STATUS, &status);
		if (status == NULL)
			throw std::exception(std::string("Shader::linkProgram glLinkProgram failed. Info log:\n\n" + getProgramInfoLog()).c_str());
	}

	void ShaderProgram::validateProgram()
	{
		glValidateProgram(m_data->getProgram());

		GLint status;
		glGetProgramiv(m_data->getProgram(), GL_VALIDATE_STATUS, &status);
		if (status == NULL)
			throw std::exception(std::string("Shader::validateProgram glValidateProgram failed. Info log:\n\n" + getProgramInfoLog()).c_str());
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