#include "texture.h"

// std includes
#include <exception>
#include <stdexcept>

// lib includes
#include "3rdparty/glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "3rdparty/stb/stb_image.h"

// mirage includes
#include "config.h"
#include "macros.h"

namespace mirage
{

	// ---------------------------------------------------------------------------
	// TextureData
	// ---------------------------------------------------------------------------

	TextureData::TextureData(
		unsigned char * image,
		int32_t width,
		int32_t height,
		int32_t components,
		bool hdr
	) :
		m_id(0),
		m_image(image),
		m_width(0),
		m_height(0),
		m_components(0),
		m_hdr(false),
		m_refAmount(0)
	{
		glGenTextures(1, &m_id);

		MLOG_DEBUG("TextureData::TextureData, created. Id: %zu", m_id);
	}

	TextureData::~TextureData()
	{
		glDeleteTextures(1, &m_id);
	}

	const GLuint TextureData::getId() const
	{
		return m_id;
	}

	void TextureData::setImage(unsigned char * image)
	{
		m_image = image;
	}

	unsigned char * TextureData::getImage()
	{
		return m_image;
	}

	void TextureData::setWidth(int32_t width)
	{
		m_width = width;
	}

	int32_t TextureData::getWidth() const
	{
		return m_width;
	}

	void TextureData::setHeight(int32_t height)
	{
		m_height = height;
	}

	int32_t TextureData::getHeight() const
	{
		return m_height;
	}

	void TextureData::setComponents(int32_t components)
	{
		m_components = components;
	}

	int32_t TextureData::getComponents() const
	{
		return m_components;
	}

	void TextureData::setHdr(bool hdr)
	{
		m_hdr = hdr;
	}

	bool TextureData::isHdr() const
	{
		return m_hdr;
	}

	void TextureData::addReference()
	{
		m_refAmount++;
	}

	void TextureData::delReference()
	{
		m_refAmount = (m_refAmount - 1 < 0) ? 0 : m_refAmount - 1;
	}

	const int32_t TextureData::getRefAmount() const
	{
		return m_refAmount;
	}

	// ---------------------------------------------------------------------------
	// Texture
	// ---------------------------------------------------------------------------

	std::map<std::string, TextureData *> LOADED_TEXTURES;

	Texture::Texture(const std::string & filePath) :
		m_filePath(filePath),
		m_data(nullptr)
	{
		TextureData * data = LOADED_TEXTURES[m_filePath];

		// This is a new texture
		if (data == nullptr)
		{
			m_data = new TextureData;
			m_data->addReference();

			// Temp objects for texture data
			int width, height, components;

			// Load texture data
			stbi_set_flip_vertically_on_load(true);
			m_data->setImage(stbi_load(m_filePath.c_str(), &width, &height, &components, 4));

			// Throw if error occurred
			if (m_data->getImage() == NULL)
			{
				throw std::runtime_error(("Texture::Texture, error.Texture failed to load! FilePath: " + m_filePath).c_str());
			}

			// Assign loaded texture's data to our data object
			m_data->setWidth(width);
			m_data->setHeight(height);
			m_data->setComponents(components);

			// Process the texture for OpenGL and upload data to GPU
			processTextureAndUploadToGPU();

			LOADED_TEXTURES[m_filePath] = m_data;
		}
		// This is an existing mesh renderer
		else
		{
			m_data = data;
			m_data->addReference();
		}

		MLOG_DEBUG("Texture::Texture, created. FilePath: %s, ref amount: %d", m_filePath.c_str(), m_data->getRefAmount());
	}

	Texture::~Texture()
	{
		m_data->delReference();

		if (m_data->getRefAmount() <= 0)
		{
			LOADED_TEXTURES.erase(m_filePath);
			MDELETES(m_data);

			MLOG_DEBUG("Texture::~Texture, destroyed. FilePath: %s", m_filePath.c_str());
		}
	}

	void Texture::bind(GLenum samplerId)
	{
		glActiveTexture(GL_TEXTURE0 + samplerId);
		glBindTexture(GL_TEXTURE_2D, m_data->getId());
	}

	const std::string Texture::getFilePath() const
	{
		return m_filePath;
	}

	TextureData * const Texture::getData()
	{
		return m_data;
	}

	void Texture::processTextureAndUploadToGPU()
	{
		// Bind the texture
		glBindTexture(GL_TEXTURE_2D, m_data->getId());

		// Specify texture dimensions, format and load the data to GPU
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_data->getWidth(), m_data->getHeight(), NULL, GL_RGBA, GL_UNSIGNED_BYTE, static_cast<void *>(m_data->getImage()));

		// Set texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Set linear filtering (mipmapping / anisotropic filtering would be setup here)
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Reset the bound texture
		glBindTexture(GL_TEXTURE_2D, NULL);
	}

}