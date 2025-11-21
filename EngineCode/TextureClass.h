#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <glad/glad.h>
#include "stb_image.h"



class TextureClass {

private:
	unsigned int m_TextureID;
	unsigned int m_Index;
	const char*  m_FilePath;

	int m_Width, m_Height, m_NrChannels;

public:

	TextureClass(unsigned int index, const char* filePath); //, unsigned int width,unsigned int height, unsigned int nrChannels
	~TextureClass();
	void Bind();

	unsigned int GetTextureID() { return m_TextureID; };
	unsigned int GetTextureIndex() { return m_Index; };




};

