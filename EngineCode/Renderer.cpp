#include "Renderer.h"
#include "glad/glad.h"

#include <iostream>




Renderer::Renderer() {};
Renderer::~Renderer() {};

void Renderer::DrawTrianglesNoIndeces(const VertexArray& va, const VertexBuffer& vb, Shader& shader) {
	shader.Bind();
	va.Bind();
	vb.Bind();

	glDrawArrays(GL_TRIANGLES, 0, vb.GetSize() );
}


void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader) {
	 //bind the shader
	shader.Bind();
	//bind va 
	va.Bind();
	//bind the ib
	ib.Bind();
	//do draw call
	//GLenum mode, GLsizei count, GLenum type, const GLvoid *indices)
	glDrawElements(GL_TRIANGLES, ib.GetCount(),GL_UNSIGNED_INT, (const void*)0);
}


void Renderer::DrawMesh(const VertexArray* va, const IndexBuffer* ib) {
	GLuint vao_id = va->GetID();
	GLuint ibo_id = ib->GetID();
	std::cout << "VAO ID AT DRAW CALL: " << vao_id << "\n\n";
	std::cout << "IBO ID AT DRAW CALL: " << ibo_id << "\n\n";
	if (vao_id == 0) {
		std::cerr << "ERROR: Invalid VAO ID (0) passed to DrawMesh." << std::endl;
		return;
	}
	if (ibo_id == 0) {
		std::cerr << "ERROR: Invalid IBO ID (0) passed to DrawMesh." << std::endl;
		return;
	}
	// Check validity using OpenGL functions
	if (!glIsVertexArray(vao_id)) {
		std::cerr << "ERROR: VAO with ID " << vao_id << " is not a valid vertex array." << std::endl;
	}
	if (!glIsBuffer(ibo_id)) {
		std::cerr << "ERROR: IBO with ID " << ibo_id << " is not a valid buffer." << std::endl;
	}
	std::cout << "ELEMENT INDICES" << ib->GetCount() << "\n\n";
	
	va->Bind();
	ib->Bind();
	glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT,nullptr);
}



void Renderer::Clear() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the depth buffer!!!

}