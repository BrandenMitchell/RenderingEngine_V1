#include "IndexBuffer.h"
#include <iostream>


IndexBuffer::IndexBuffer() {
	glGenBuffers(1, &m_RendererID);
}



IndexBuffer::IndexBuffer(const void* data, const unsigned int count) {
	m_Count = count;
	//Generate buffer
	glGenBuffers(1, &m_RendererID);
	std::cout << "IB constructor called with ID: " << m_RendererID << '\n';

	//bind buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

	//populate buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}


void IndexBuffer::PopulateBuffer(std::vector<unsigned int> indices)  {
	m_Count = indices.size() * sizeof(unsigned int);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}


IndexBuffer::~IndexBuffer() {
	if (m_RendererID != 0) {
		glDeleteBuffers(1, &m_RendererID);
		std::cout << "IB destructor called with ID: " << m_RendererID << '\n';
	}
}

void IndexBuffer::Bind() const {
	std::cout << "bound IBO with ID: " << m_RendererID << std::endl;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
};

void IndexBuffer::SetCount(unsigned int count) {
	m_Count = count;

}
void IndexBuffer::UnBind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


