#include "Mesh.h"
#include <iomanip> 

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
	std::cout << "mesh constructor called" << "\n\n";
	this->vertices = vertices;
	this->indices = indices;
	this->hasShader = false;

	SetUpMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
	std::cout << "mesh constructor Called with Textures " << '\n';
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures; // this is the textures
	std::cout << this->textures.size()<<std::endl;
	this->hasShader = false;


	SetUpMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, const char* vertPath, const char* fragPath) {
	std::cout << "mesh constructor Called with Shaders " << '\n';
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures; // this is the textures
	std::cout << this->textures.size() << std::endl;
	this->hasShader = true;
	m_MeshShaderID.ShaderFileSetup(vertPath, fragPath);

	SetUpMesh();
}


Mesh::~Mesh() {
	std::cout << "Mikes a bitch: # I GET NO BITCHESS= Mike:" << std::endl;
	VAO.UnBind();
	VBO.UnBind();
	IBO.UnBind();
	if (hasShader) {
		m_MeshShaderID.unBind();
	}
}


void Mesh::PopulateBuffers(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
	this->vertices = vertices;
	this->indices = indices;
	SetUpMesh();
}

void Mesh::AddShader(const char* vertPath, const char* fragPath) {
	hasShader = true;
	m_MeshShaderID.ShaderFileSetup(vertPath, fragPath);
}

void Mesh::SetUpMesh() {
	//setup the shi to draw
	VAO.Bind();
	VBO.Bind();
	IBO.Bind();

	VBO.VertexBufferPopulate(vertices);
	IBO.PopulateBuffer(indices);

	unsigned int size = vertices.size() * sizeof(Vertex);
	
	//VAO layout shit
	//positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	if (!isLight) {
		//normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

		//Texture Coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextCoords));

	}
	VAO.UnBind();
}

void Mesh::Draw(Renderer &renderer) {
	for (int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + textures[i].index);
		glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
	}
	renderer.DrawMesh(&VAO, &IBO);
}

void Mesh::addTexture(Texture texture) {
	this->textures.emplace_back(texture);
}

void Mesh::addUniform(std::string name, uniformTypes type, std::variant<unsigned int, float, float*,glm::vec3, glm::vec4> value) {
	uniformData data{ type,value };
	uniformBuffer.insert({ name,data });
}


void Mesh::SetUniforms() {
	std::cout <<"SIZED OF BUFFER::"<< uniformBuffer.size() << std::endl;
	for (const auto& pair : uniformBuffer) {
		std::string name = pair.first;

		std::cout << name << std::endl;
		switch (pair.second.type) {
			case(ONEINT) : {
				
				m_MeshShaderID.SetUniform1i(name, std::get<unsigned int>(pair.second.value));
				break;
			}
			case(ONEFLOAT): {
				m_MeshShaderID.SetUniform1f(name, std::get<float> (pair.second.value));
				break;
			}
			case(THREEFLOAT): {
				m_MeshShaderID.setUniform3f(name, std::get<glm::vec3>(pair.second.value).x, std::get<glm::vec3>(pair.second.value).y, std::get<glm::vec3>(pair.second.value).z);
				break;
			}
			case(FOURFLOAT): {
				m_MeshShaderID.SetUniform4f(name, std::get<glm::vec4>(pair.second.value).x, std::get<glm::vec4>(pair.second.value).y, std::get<glm::vec4>(pair.second.value).z, std::get<glm::vec4>(pair.second.value).w);
				break;
			}
			case(MATFOUR): {
				m_MeshShaderID.setUniformMatrix4(name, std::get<float*>(pair.second.value));
				break;
			}
			default: {
				std::cout << "Default switch shitter" << "\n";
				break;
			}
		}
	}
}


glm::mat4 Mesh::UpdateModelMatrix(glm::vec3 pos) {
	this->meshModelMatrix = glm::mat4(1.0f);
	this->meshModelMatrix = glm::translate(this->meshModelMatrix, pos);
	return this->meshModelMatrix;
}


void Mesh::PrintModelMatrix() {
	std::cout << "GLM Matrix 4x4:" << std::endl;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			std::cout << std::fixed << std::setprecision(4) << this->meshModelMatrix[j][i] << "\t"; // Note: GLM stores in column-major order
		}
		std::cout << std::endl;
	}
}