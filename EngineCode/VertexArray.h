#pragma once
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
class VertexArray {
private:
	unsigned int m_RendererID;

public: 
	VertexArray();
	~VertexArray();


	void Bind() const;
	void UnBind() const;

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const; // this is how we add a layout and a vb to our vao 
	unsigned int GetID() const { return m_RendererID; };
	//preventing copying
	VertexArray(const VertexArray&) = delete;
	VertexArray& operator = (const VertexArray&) = delete;

	//allow moving 
	VertexArray(VertexArray&& other) noexcept;
	VertexArray& operator = (VertexArray&& other) noexcept;

};

