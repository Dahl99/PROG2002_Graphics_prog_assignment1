#include <GL/glew.h>
#include "shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

namespace framework
{
	Shader::Shader(const std::string& vertPath, const std::string& fragPath) 
		: vertPath(vertPath), fragPath(fragPath), m_RendererID(0)	//	Initializing values
	{
		//	Reading shaders from file
		const std::string vsrc = ParseShader(vertPath);
		const std::string fsrc = ParseShader(fragPath);

		//	Creating, compiling and attaching shaders
		m_RendererID = CreateShader(vsrc, fsrc);
	}

	Shader::~Shader()	//	Deletes shader when out of scope
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const	//	Binding/activating the shader
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const	//	Unbinds/disables the shader
	{
		glUseProgram(0);
	}

	void Shader::SetUniform1i(const std::string& name, int value)	//	Specifying a value for integer uniform
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)	//	Specifying a value for matrix uniform
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}

	GLuint Shader::getUniformLocation(const std::string& name)	//	Gets the uniform location
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		return location;
	}

	std::string Shader::ParseShader(const std::string& filepath)	//	Reads shaders from file
	{
		std::ifstream file(filepath);

		std::string out;
		std::string line;

		while (std::getline(file, line))
		{
			out += line + '\n';
		}

		file.close();

		return out;	//	Returning shader
	}

	GLuint Shader::CompileShader(unsigned int type, const std::string& source)
	{
		//			Creating and compiling shaders
		GLuint id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!\n" << message << std::endl;
			glDeleteShader(id);

			return 0;
		}

		return id;
	}

	GLuint Shader::CreateShader(const std::string& vertShader, const std::string& fragShader)
	{
		//	Creating shader program and calling for compilation
		GLuint program = glCreateProgram();
		GLuint vs = CompileShader(GL_VERTEX_SHADER, vertShader);
		GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragShader);

		//		Attaching and linking shaders before validation
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		//		Deleting shaders
		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;	//	Returning finished shader program
	}
}