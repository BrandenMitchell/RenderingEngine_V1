#pragma once
#include "ShaderClass.h"
#include "VertexArray.h"
#include "IndexBuffer.h"



class Renderer {
private:
	unsigned int m_RendererID;



public:
	Renderer();
	~Renderer();

	void DrawTrianglesNoIndeces(const VertexArray& va, const VertexBuffer& vb, Shader& shader);
	void Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader);
	void DrawMesh(const VertexArray* va, const IndexBuffer* ib);
	void Clear();
	inline unsigned int GetRendererID() { return m_RendererID; };
};

