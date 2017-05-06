#ifndef TEXTURE_H
#define TEXTURE_H

// std includes
#include <string>
#include <vector>
#include <map>

typedef unsigned int GLuint;
typedef unsigned int GLenum;

namespace mirage
{

	class TextureData
	{
	public:
		TextureData(
			unsigned char * image = NULL,
			int32_t width = 0,
			int32_t height = 0,
			int32_t components = 0,
			bool hdr = false
		);
		~TextureData();

		const GLuint getId() const;
		void setImage(unsigned char * image);
		unsigned char * getImage();
		void setWidth(int32_t width);
		int32_t getWidth() const;
		void setHeight(int32_t height);
		int32_t getHeight() const;
		void setComponents(int32_t components);
		int32_t getComponents() const;
		void setHdr(bool hdr);
		bool isHdr() const;
		void addReference();
		void delReference();
		const int32_t getRefAmount() const;
	private:
		GLuint m_id;
		unsigned char * m_image;
		int32_t m_width;
		int32_t m_height;
		int32_t m_components;
		bool m_hdr;
		int32_t m_refAmount;
	};

	extern std::map<std::string, TextureData *> LOADED_TEXTURES;

	class Texture
	{
	public:
		Texture(const std::string & filePath);
		~Texture();

		void bind(GLenum samplerId);
		const std::string getFilePath() const;
		TextureData * const getData();
	private:
		void processTextureAndUploadToGPU();

		std::string m_filePath;
		TextureData * m_data;
	};

}


#endif // TEXTURE_H