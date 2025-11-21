#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "TextureClass.h"
#include "glm/glm.hpp"
#include "Mesh.h"
#include "Renderer.h"
#include "Camera.h"
#include "ShaderClass.h"


enum LightTypes {
	POINT,
	SPOTLIGHT,
	DIRLIGHT
};



//struct LightObj {
//	glm::vec3 position;
//	glm::vec3 direction;
//
//	glm::vec3 ambient;
//	glm::vec3 diffuse;
//	glm::vec3 specular;
//
//	float constant;
//	float linear;
//	float quadratic;
//	float cutOff;
//	float outerCutOff;
//};


class Scene {
	

private:
	std::vector<std::unique_ptr<Mesh>> meshObjs;
	//Renderer m_Renderer;
	Camera m_Camera;
	Shader m_globalShader;

	//camera matrices identity
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 currentMeshModel = glm::mat4(1.0f); 
	unsigned int  SCR_WIDTH = 1200;
	unsigned int  SCR_HEIGHT = 800;

public:
	float testVal = 0.0;
	Scene();
	~Scene();

	void CreateScene(unsigned int screenWidth, unsigned int screenHeight);
	void DrawScene(Renderer& renderer); //render all scene objs
	void UpdateScene(Renderer& renderer, glm::vec3 pos); //update all transforms, texures etc for game objs
	void UpdateMatrices();



	std::vector<Vertex> MakeVertexVector(float vertices[], int floatsPerVertex);

	void ProcessKeyboardMovement(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset);
	void ProcessMouseScroll(float yoffset);
	glm::mat4 GetProjection() { return projection; };
	glm::mat4 GetView() { return view; };


};

