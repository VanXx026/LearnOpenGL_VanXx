#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>;

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	unsigned int Id;

	Shader(const char* vertexPath, const char* fragmentPath)
	{
		// 1. 从文件路径读取顶点/片段着色器
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// 保证ifstream对象可以抛出异常
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// 打开文件
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// 读取文件的缓冲内容到数据流中
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// 关闭文件处理器
			vShaderFile.close();
			fShaderFile.close();
			// 转换数据流到string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		// 2. 编译和链接着色器
		// compile
		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vShaderCode, NULL);
		glCompileShader(vertexShader);
		check_shader_Fail(vertexShader, GL_COMPILE_STATUS);
		unsigned int fragShader;
		fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fShaderCode, NULL);
		glCompileShader(fragShader);
		check_shader_Fail(fragShader, GL_COMPILE_STATUS);
		// link
		Id = glCreateProgram();
		glAttachShader(Id, vertexShader);
		glAttachShader(Id, fragShader);
		glLinkProgram(Id);
		check_shader_Fail(Id, GL_LINK_STATUS);

		glDeleteShader(vertexShader);
		glDeleteShader(fragShader);
	}
	// shader use
	void use()
	{
		glUseProgram(Id);
	}
	// uniform
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(Id, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(Id, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(Id, name.c_str()), value);
	}
	void setFloat3(const std::string& name, float x, float y, float z)
	{
		glUniform3f(glGetUniformLocation(Id, name.c_str()), x, y, z);
	}
	void setFloat4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(Id, name.c_str()), x, y, z, w);
	}
private:
	void check_shader_Fail(GLuint shader, GLenum status)
	{
		int  success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			if (status == GL_COMPILE_STATUS)
			{
				std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
			}
			if (status == GL_LINK_STATUS)
			{
				std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
			}
		}
	}
};

#endif // !SHADER_H

