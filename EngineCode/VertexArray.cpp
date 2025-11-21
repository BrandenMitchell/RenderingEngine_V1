#include "VertexArray.h"
#include "glad/glad.h"
#include <iostream>


VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_RendererID);
	std::cout << "VA constructor called with ID: " << m_RendererID << '\n';
}

VertexArray::~VertexArray() {
	if (m_RendererID != 0) {
		glDeleteVertexArrays(1, &m_RendererID);
		std::cout << "VA destructor called with ID: " << m_RendererID << '\n';
	}
}

void VertexArray::Bind() const {
	glBindVertexArray(m_RendererID);
}

void VertexArray::UnBind() const {
	glBindVertexArray(0);
}

// this is how we add a layout and a vb to our vao 
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const {
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int elementSize = elements.size();
	unsigned int offset = 0;
	for (int i = 0; i < elementSize; i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
};


VertexArray::VertexArray(VertexArray&& other) noexcept
	: m_RendererID(other.m_RendererID){
	other.m_RendererID = 0;
}

VertexArray& VertexArray::operator = (VertexArray&& other) noexcept {
	if (this != &other) {
		glDeleteBuffers(1, &m_RendererID);
		m_RendererID = other.m_RendererID;
		other.m_RendererID = 0;
	}
	return *this;
}

