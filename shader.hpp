#ifndef SHADeR_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader{
	public:
		// program ID
		unsigned int ID;

		// constructor reads and builds shader
		Shader(const char* vertexPath, const char* fragmentPath){
			// Get vertex and fragment shader code
			std::string vertexCode;
			std::string fragmentCode;
			std::ifstream vShaderFile;
			std::ifstream fShaderFile;

			// ensure ifstream objects can throw exceptions
			vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
			fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

			try
			{
				// open files
				vShaderFile.open(vertexPath);
				fShaderFile.open(fragmentPath);
				std::stringstream vShaderStream, fShaderStream;

				// Read file buffer content into streams
				vShaderStream << vShaderFile.rdbuf();
				fShaderStream << fShaderFile.rdbuff();
				// Close file handlers
				vShaderFile.close();
				fShaderFile.close();

				// convert stream into string
				vertexCode = vShaderStream.str();
				fragmentCode = fShaderStream.str(;)
			}
			catch(std::ifstream::failure e){
				std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
			}
			const char* vShaderCode = vertexCode.c_str();
			const char* fShaderCode = fragmentCode.c_str();

			// compile shaders
			unsigned int vertex, fragment;
			int success;
			char infoLog[512];

			// vertex Shader
			vertex = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex, 1, &vShaderCode, NULL);
			glCompileShader(vertex);
			// print errors
			if(!sucess){
				glGetShaderInfoLog(vertex, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog <<std::endl;
			}

			// fragment Shader
			fragment = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(fragment, 1, &fShaderCode, NULL);
			glCompileShader(fragment);
			// print errors
			if(!sucess){
				glGetShaderInfoLog(fragment, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog <<std::endl;
			}
			
			// Shader Program
			ID = glCreateProgram();
			glAttachShader(ID, vertex);
			glAttachShader(ID, fragment);
			glLinkProgram(ID);
			// check linking errors
			glGetProgramiv(ID, GL_LINK_STATUS, &success);
			if(!success){
				glGetProgramInfoLog(ID, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			}

			// delete shaders after linked
			glDeleteShader(vertex);
			glDeleteShader(fragment);
		}

		// use/activate shader
		void use(){
			glUseProgram(ID);
		}

		// utility uniform functions
		void setBool(const std::string &name, bool value)const{
			glUniformli(glGetUniformLocation(ID, name.c_str()), int(value));
		}
		void setInt(const std::string &name, int value)const{
			glUniformli(glGetUniformLocation(ID, name.c_str()), value);
		}
		void setFloat(const std::string &name, float value)const{
			glUniformli(glGetUniformLocation(ID, name.c_str()), value);
		}

};

#endif
		
