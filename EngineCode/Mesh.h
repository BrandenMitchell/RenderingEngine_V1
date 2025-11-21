#pragma once

#include <string>
#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>-
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ShaderClass.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include <variant>

enum uniformTypes {
	ONEINT,
	ONEFLOAT,
	THREEFLOAT,
	FOURFLOAT,
	MATFOUR
};


struct uniformData {
	uniformTypes type;
	//std::string uniformName;
	std::variant<unsigned int, float, float*,glm::vec3, glm::vec4> value;
};




struct Texture {
	unsigned int id;   //this is the ID duuhhhhh
	std::string type; // this will be like TEXTURE_2D or some shit
	unsigned int index;
};



class Mesh {
	
protected: 
	// render ID's
	VertexArray VAO;
	VertexBuffer VBO;
	IndexBuffer IBO;

	void SetUpMesh();
	glm::mat4 meshModelMatrix = glm::mat4(1.0f); //initialize to identity matrix
	glm::vec3 position = glm::vec3(-1.7f, 3.0f, 1.0f);



public: 
	
	bool hasShader = false;
	bool isLight = false;
	Shader m_MeshShaderID;

	//mesh data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	std::unordered_map < std::string, uniformData> uniformBuffer;

	Mesh() = default;
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, const char* vertPath, const char* fragPath);

	~Mesh();
	

	void PopulateBuffers(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

	void Draw(Renderer& renderer);
	glm::mat4 UpdateModelMatrix(glm::vec3 pos);
	void addTexture(Texture texture);
	void addUniform(std::string name, uniformTypes type, std::variant<unsigned int, float, float*, glm::vec3, glm::vec4> value);
	void AddShader(const char* vertPath, const char* fragPath);
	void SetPosition(glm::vec3 newPos) { position = newPos; };
	void SetUniforms();
	glm::vec3 GetPosition() { return position; };
	glm::mat4 GetModelMatrix() { return meshModelMatrix; };
	void PrintModelMatrix();
	VertexArray* GetVAO() { return &VAO; };
	VertexBuffer* GetVBO() { return &VBO; };
	IndexBuffer* GetIBO() { return &IBO; };


	Mesh(Mesh&& other) noexcept
		: vertices(std::move(other.vertices)),
		indices(std::move(other.indices)),
		textures(std::move(other.textures)),
		VAO(std::move(other.VAO)),
		VBO(std::move(other.VBO)),
		IBO(std::move(other.IBO)),
		hasShader(std::move(other.hasShader)),
		m_MeshShaderID(std::move(other.m_MeshShaderID)),
		position(std::move(other.position)),
		meshModelMatrix(std::move(other.meshModelMatrix)),
		uniformBuffer(std::move(other.uniformBuffer))
	{
	}

	Mesh& operator=(Mesh&& other) noexcept
	{
		if (this != &other) {
			vertices = std::move(other.vertices);
			indices = std::move(other.indices);
			textures = std::move(other.textures);
			VAO = std::move(other.VAO);
			VBO = std::move(other.VBO);
			IBO = std::move(other.IBO);
			hasShader = std::move(other.hasShader);
			m_MeshShaderID = std::move(other.m_MeshShaderID);
			position = std::move(other.position);
			meshModelMatrix = std::move(other.meshModelMatrix);
			uniformBuffer= std::move(other.uniformBuffer);
		}
		return *this;
	}

	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;
};

