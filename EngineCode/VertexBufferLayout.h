#pragma once

#include <glad/glad.h>
#include <vector>





struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) {
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}
		return 0;
	}

};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> m_Elements; //container for our buffer elements, an element is one attribute in a vertex
	unsigned int m_Stride;

public:
	VertexBufferLayout() :
		m_Stride(0) {}

	std::vector<VertexBufferElement> GetElements() const ; //return the whole list of elements s
	unsigned int GetStride() const; //return the stride

	template<typename T> 
	void Push(unsigned int count) {}; //add a layout
};

template<>
inline void VertexBufferLayout::Push<float>(unsigned int count) {
	m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);

};


template<>
inline void VertexBufferLayout::Push<unsigned int >(unsigned int count) {
	m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
};


template<>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count) {
	m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
};