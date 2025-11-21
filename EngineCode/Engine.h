#pragma once
#include <glad/glad.h> //must include glad before glfw bc glad has the required openGL headers needed for other libs
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "InitGLFW.h"
#include "Renderer.h"
#include "Camera.h"
#include "Scene.h"
#include "ShaderClass.h"





enum EngineState {
	ENGINE_RUNNING,
	ENGINE_SHUTTING_DOWN
};



class Engine {


private:
	GLFWwindow* m_WindowID;
	Renderer m_Renderer;
	Scene m_Scene;

	



	//engine State
	EngineState State = ENGINE_RUNNING;

	unsigned int m_EngineID;

	//window shit
	const char* m_WindowTitle;
	unsigned int  SCR_WIDTH = 1200;
	unsigned int  SCR_HEIGHT = 800;




	// Static wrapper functions for GLFW callbacks
	static void mouse_callback_wrapper(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback_wrapper(GLFWwindow* window, double xoffset, double yoffset);
	



	float lastMouseX = SCR_WIDTH / 2; 
	float lastMouseY = SCR_HEIGHT / 2; //holds the init for the center of the screen
	bool firstMouseUse = true; //has the mouse been used yet (used to offset shake when the camera first focuses the screen)
	float deltaTime = 0.0f;		//normalize time so that framerate has no effect on things like movement 
	float lastFrame = 0.0f;		//hold the time of the last captured frame



public:
	
	
	Engine(unsigned int width, unsigned int height, const char* title);
	~Engine();

	
	int Init();
	void Run();
	void ShutDown();

	float calcDeltaTime();

	void processInput(GLFWwindow* window);
	void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);
	void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	};


};

