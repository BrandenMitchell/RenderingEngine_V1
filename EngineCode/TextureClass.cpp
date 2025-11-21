#include "TextureClass.h"


TextureClass::TextureClass(unsigned int index,const char* filePath) {
	m_Index = index;
	/*m_Width = width;
	m_Height = height;
	m_NrChannels = nrChannels;*/
	m_FilePath = filePath;

	//init the texture 
    
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    //set the texture wrapping and filtering opitons for the currently bound texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    
    unsigned char* data = stbi_load( m_FilePath, &m_Width, &m_Height, &m_NrChannels, 0);
    if (data) {
        GLenum format;
        if (m_NrChannels == 1)
            format = GL_RED;
        else if (m_NrChannels == 3)
            format = GL_RGB;
        else if (m_NrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    else {
        std::cout << "ERROR::GENERATING::TEXTURE::COULD::NOT::LOAD" << std::endl;
    }
    stbi_image_free(data);
}


TextureClass::~TextureClass() {
    //do some destructor shit ig
}


void TextureClass::Bind() {
    glActiveTexture(GL_TEXTURE0 + m_Index);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

