#include "Engine.h"
#include "ShaderClass.h"
#include <iostream>
#include <string>
#include <cstdlib> // For rand(), srand()



Engine::Engine(unsigned int width, unsigned int height, const char* title)
    : SCR_WIDTH(width), SCR_HEIGHT(height), m_WindowTitle(title)
{};


Engine::~Engine() { ; }


int Engine::Init() {
    
    if (!glfwInit()) {
        std::cout << "LOG::INIT::ERR::GLFW_FAILED_TO_INIT" << "\n\n";
    };

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_WindowID = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, m_WindowTitle, nullptr, nullptr);
    std::cout << "WIDTH: " << SCR_WIDTH << "Height: " << SCR_HEIGHT << std::endl;
    if (!m_WindowID) {
        std::cout << "ERROR::WINDOWERR::windowOBJ::NULL" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(m_WindowID);
    glfwSwapInterval(1);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "ERROR::GLADLOAD::NULL" << std::endl;
        return -1;
    }

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSetInputMode(m_WindowID, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(m_WindowID, this);
};


void Engine::Run() {
    glfwSetFramebufferSizeCallback(m_WindowID, framebuffer_size_callback);
    glfwSetCursorPosCallback(m_WindowID, mouse_callback_wrapper);
    glfwSetScrollCallback(m_WindowID, scroll_callback_wrapper);
    glEnable(GL_DEPTH_TEST);
    std::vector<glm::vec3> cubePostions = {

        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)

    };
    
    m_Scene.CreateScene(1200, 800);
    int randomIndex = std::rand() % cubePostions.size();
    while (!glfwWindowShouldClose(m_WindowID)) {
        float deltaTime = calcDeltaTime();
        processInput(m_WindowID);
        m_Renderer.Clear();
        glm::vec3 pos = cubePostions[randomIndex];
        m_Scene.UpdateMatrices();
        m_Scene.UpdateScene(m_Renderer, pos);
        m_Scene.DrawScene(m_Renderer);

        glfwSwapBuffers(m_WindowID);
        glfwPollEvents();
    }

    glfwTerminate();
}


void Engine::ShutDown() {
    
};
void Engine::processInput(GLFWwindow* window) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        State = ENGINE_SHUTTING_DOWN;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        m_Scene.ProcessKeyboardMovement(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        m_Scene.ProcessKeyboardMovement(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        m_Scene.ProcessKeyboardMovement(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        m_Scene.ProcessKeyboardMovement(RIGHT, deltaTime);
    }
};
void Engine::mouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float> (xposIn);
    float ypos = static_cast<float> (yposIn);
    if (firstMouseUse) {
        lastMouseX = xpos;
        lastMouseY = ypos;
        firstMouseUse = false;
    }

    float xoffset = xpos - lastMouseX;
    float yoffset = lastMouseY - ypos;
    lastMouseX = xpos;
    lastMouseY = ypos;

    m_Scene.ProcessMouseMovement(xoffset, yoffset);
}
void Engine::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    m_Scene.ProcessMouseScroll(static_cast<float>(yoffset));
}
void Engine::mouse_callback_wrapper(GLFWwindow* window, double xpos, double ypos) {
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    if (engine) {
        engine->mouseCallback(window, xpos, ypos);
    }
}
void Engine::scroll_callback_wrapper(GLFWwindow* window, double xoffset, double yoffset) {
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    if (engine) {
        engine->scrollCallback(window, xoffset, yoffset);
    }
}
float Engine::calcDeltaTime() {
    float currentFrame = static_cast<float> (glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    return deltaTime;
}