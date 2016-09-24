#pragma once

#ifndef SHADERHEADER_H
#define SHADERHEADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


#include <GLFW\glew.h>

using namespace std;

// =========================================
// --- Class for loading in the shaders ---
// =========================================
class Shader
{
public:

	GLuint shaderProgram;

	// ========================================
	// --- Constructor For Getting Shaders ---
	// ========================================
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
	{

		string vertexCode;
		string fragmentCode;
		ifstream vShaderFile;
		ifstream fShaderFile;

		vShaderFile.exceptions(ifstream::badbit);
		fShaderFile.exceptions(ifstream::badbit);

		// ==============================================
		// --- Opens the Files and Loads the Shaders ---
		// ==============================================
		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

		}
		catch (ifstream::failure e)
		{
			cout << "ERROR::UNABLE TO READ SHADER FILES!!" << endl;
		}

		const GLchar* vShaderCode = vertexCode.c_str();
		const GLchar* fShaderCode = fragmentCode.c_str();

		// ==============================
		// --- Shader Initialization ---
		// ==============================
		GLuint vertex, fragment;
		GLint success;
		GLchar infoLog[512];

		// ======================
		// --- Vertex Shader ---
		// ======================
		vertex = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			cout << "ERROR::FAILED TO COMPILE VERTEX SHADER\n" << infoLog << endl;
		}
		else
		{
			cout << "VERTEX COMPILED" << endl;
		}

		// ========================
		// --- Fragment Shader ---
		// ========================
		fragment = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			cout << "ERROR::FAILED TO COMPILE FRAGMENT SHADER\n" << infoLog << endl;
		}
		else
		{
			cout << "FRAGMENT COMPILED" << endl;
		}

		// =====================================
		// --- Program and Link the Shaders ---
		// =====================================
		this->shaderProgram = glCreateProgram();

		glAttachShader(this->shaderProgram, vertex);
		glAttachShader(this->shaderProgram, fragment);
		glLinkProgram(this->shaderProgram);

		glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);

		if (!success) 
		{
			glGetProgramInfoLog(this->shaderProgram, 512, NULL, infoLog);
			cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << endl;
		}
		else
		{
			cout << "SHADERS COMPILED" << endl;
		}
		
		// ===========================
		// --- Delete the Shaders ---
		// ===========================
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	// ===================================================
	// --- Use Function to Allow us to Access Shaders ---
	// ===================================================
	void Use()
	{
		glUseProgram(this->shaderProgram);
	}
};

#endif