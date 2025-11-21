
#include "ShaderClass.h"
#pragma message("Including ShaderClass.h")



#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map> //hashmap


Shader::Shader(const char* vertPath, const char* fragPath) {
	std::cout << vertPath << fragPath << std::endl;
	std::stringstream vertexStream;
	std::stringstream fragmentStream;
	std::string vertexFileSource;
	std::string fragmentFileSource;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		//open files
		vShaderFile.open(vertPath);
		fShaderFile.open(fragPath);

		//read file data into string stream
		vertexStream << vShaderFile.rdbuf();
		fragmentStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexFileSource = vertexStream.str();
		fragmentFileSource = fragmentStream.str();

	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::SHADER_FILE_NOT_OPEN::" << std::endl;
	}

	//Shader data has been grabbed from the file annd put in a string
	//convert that string to a c_string for the open gl calls
	const char* vertexShaderData = vertexFileSource.c_str();
	const char* fragmentShaderData = fragmentFileSource.c_str();

	//create vertex and frag shaders
	unsigned int vertShader;
	unsigned int fragShader;
	int success;
	char infoLog[512];
	//get Shader id's
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	//apply shader source to the id's
	glShaderSource(vertShader, 1, &vertexShaderData, nullptr);
	glShaderSource(fragShader, 1, &fragmentShaderData, nullptr);
	
	// Compile shaders
	glCompileShader(vertShader);

	//error check compile
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILE::ERROR\n" << infoLog << std::endl;
	}
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILE::ERROR\n" << infoLog << std::endl;
	}
	// Create program and link shaders
	m_ShaderProgramID = glCreateProgram();

	glAttachShader(m_ShaderProgramID, vertShader);
	glAttachShader(m_ShaderProgramID, fragShader);

	glLinkProgram(m_ShaderProgramID);

	glGetProgramiv(m_ShaderProgramID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_ShaderProgramID, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK::ERROR\n" << infoLog << std::endl;
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

};

Shader::~Shader() {
	glDeleteProgram(m_ShaderProgramID);
};


void Shader::Bind() const {
	std::cout << "THIS SHADER IS WHAT WE BINDING: " <<m_ShaderProgramID<< '\n';
	GLint status;
	glValidateProgram(m_ShaderProgramID);
	glGetProgramiv(m_ShaderProgramID, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE) {
		std::cout << "SHADER IS GEEEEEKEDDDD" << std::endl;
	}
	glUseProgram(m_ShaderProgramID);
};



void Shader::unBind() const {
	glUseProgram(0);
};



void Shader::SetUniform4f(const std::string& uniformName, float v0, float v1, float v2, float v3) {
	glUniform4f(GetUniformLocation(uniformName), v0, v1, v2, v3);

};

void Shader::ShaderFileSetup(const char* vertPath, const char* fragPath) {
	std::cout << vertPath << fragPath << std::endl;
	std::stringstream vertexStream;
	std::stringstream fragmentStream;
	std::string vertexFileSource;
	std::string fragmentFileSource;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		//open files
		vShaderFile.open(vertPath);
		fShaderFile.open(fragPath);

		//read file data into string stream
		vertexStream << vShaderFile.rdbuf();
		fragmentStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexFileSource = vertexStream.str();
		fragmentFileSource = fragmentStream.str();

	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::SHADER_FILE_NOT_OPEN::" << std::endl;
	}

	//Shader data has been grabbed from the file annd put in a string
	//convert that string to a c_string for the open gl calls
	const char* vertexShaderData = vertexFileSource.c_str();
	const char* fragmentShaderData = fragmentFileSource.c_str();

	//create vertex and frag shaders
	unsigned int vertShader;
	unsigned int fragShader;
	int success;
	char infoLog[512];
	//get Shader id's
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	//apply shader source to the id's
	glShaderSource(vertShader, 1, &vertexShaderData, nullptr);
	glShaderSource(fragShader, 1, &fragmentShaderData, nullptr);

	// Compile shaders
	glCompileShader(vertShader);

	//error check compile
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILE::ERROR\n" << infoLog << std::endl;
	}
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILE::ERROR\n" << infoLog << std::endl;
	}
	// Create program and link shaders
	m_ShaderProgramID = glCreateProgram();

	glAttachShader(m_ShaderProgramID, vertShader);
	glAttachShader(m_ShaderProgramID, fragShader);

	glLinkProgram(m_ShaderProgramID);

	glGetProgramiv(m_ShaderProgramID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_ShaderProgramID, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK::ERROR\n" << infoLog << std::endl;
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

void Shader::setUniform3f(const std::string& uniformName, float v0, float v1, float v2) {
	glUniform3f(GetUniformLocation(uniformName), v0, v1, v2);

};



void Shader::SetUniform1i(const std::string& uniformName, unsigned int v1) {
	glUniform1i(GetUniformLocation(uniformName), v1);
}

void Shader::SetUniform1f(const std::string& uniformName, float v1) {
	glUniform1f(GetUniformLocation(uniformName), v1);

}


void Shader::setUniformMatrix4(const std::string& name, glm::mat4& transMatrix) {
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(transMatrix));

}
void Shader::setUniformMatrix4(const std::string& name, float* matrix) {
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, matrix);
}



int Shader::GetUniformLocation(const std::string& uniformName) {
	if (m_UniformLocationCache.find(uniformName) != m_UniformLocationCache.end()) {
		return m_UniformLocationCache[uniformName]; //if its in the cache just send it back
	}

	int location = glGetUniformLocation(m_ShaderProgramID, uniformName.c_str());
	if (location == -1) {
		std::cout << "UNIFORM::" << uniformName << " Does not exist!" << "\n";
		return location;
	}
	m_UniformLocationCache[uniformName] = location;
	return location;

};

