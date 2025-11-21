#pragma once
#include <glad/glad.h>
#include <unordered_map>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader {
private: 
	unsigned int m_ShaderProgramID;

	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader() = default;

	Shader(const char* vertPath, const char* fragPath);

	~Shader();


	void Bind() const;
	void unBind() const;
	void ShaderFileSetup(const char* vertPath, const char* fragPath);
	void SetUniform4f(const std::string& uniformName, float v0, float v1, float v2, float v3); // uniform 4f takes in 4 values 
	void setUniform3f(const std::string& uniformName,float v0, float v1, float v2);
	int  GetUniformLocation(const std::string& uniformName); 	//get the location of a uniform in a program
	void SetUniform1i(const std::string& uniformName, unsigned int v1);
	void SetUniform1f(const std::string& uniformName, float v1);
	void setUniformMatrix4(const std::string& name, glm::mat4& transMatrix);
	void setUniformMatrix4(const std::string& name, float* matrix);
	unsigned int GetShaderProgramID() { return m_ShaderProgramID; };

	Shader(Shader&& other) noexcept
		: m_ShaderProgramID(other.m_ShaderProgramID)
	{
		other.m_ShaderProgramID = 0;
	}

	Shader& operator=(Shader&& other) noexcept
	{
		if (m_ShaderProgramID != 0)
			glDeleteProgram(m_ShaderProgramID);

		m_ShaderProgramID = other.m_ShaderProgramID;
		other.m_ShaderProgramID = 0;
		return *this;
	}

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;



};

