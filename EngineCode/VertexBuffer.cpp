#include "VertexBuffer.h"
#include <glad/glad.h>
#include <iostream>




VertexBuffer::VertexBuffer() {
	glGenBuffers(1, &m_RendererID);
	//glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}


VertexBuffer::VertexBuffer(const void* data, const unsigned int size) {
	m_Count = size / sizeof(float);
	m_Size = size;

	//Generate buffer
	glGenBuffers(1, &m_RendererID);

	//bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

	//populate buffer
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	std::cout << "VB constructor called with ID: " << m_RendererID << '\n';
}


void VertexBuffer::VertexBufferPopulate(std::vector<Vertex> vertices) {
	unsigned int size = vertices.size() * sizeof(Vertex);

	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, &vertices[0] , GL_STATIC_DRAW);

}


VertexBuffer::~VertexBuffer() {
	if (m_RendererID != 0) {
		glDeleteBuffers(1, &m_RendererID);
		std::cout << "VB destructor called with ID: " << m_RendererID << '\n';
	}
}


void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}


void VertexBuffer::UnBind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

