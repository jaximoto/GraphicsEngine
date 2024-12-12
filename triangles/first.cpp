#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

void ProcessInput(GLFWwindow *window){
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// Vertex Shader
const char *vertexShaderSource = 
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"out vec4 vertexColor;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"	vertexColor = vec4(0.5, 0.0, 0.0, 1);\n"
	"}\0";

// Fragment Shader
const char *fragmentShaderSource =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"uniform vec4 ourColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = ourColor;\n"
	"}\0";

// Callback func to sync viewport with window on resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
glViewport(0, 0, width, height);
}

int main(){
	// Make Window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Rainbow Triangle", NULL, NULL);
	if (window == NULL){
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Failed to init GLAD" << std::endl;
		return -1;
	}

	// Specify viewport for openGL
	glViewport(0, 0, 800, 600);
	

	// Tell GLFW to call my func on resize
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Vertex Shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Check if it compiled
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success){
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION FAILED\n" << infoLog;
	}

	// Frag Shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Check if it compiled
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success){
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION FAILED\n" << infoLog;
	}

	// Make Shader Program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check if linked correctly
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success){
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINKING::FAILED\n" << infoLog;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
	        0.5f, -0.5f, 0.0f,
	        0.0f,  0.5f, 0.0f
					      
	};  
	// Init Objects
	unsigned int VBO, VAO;

	// VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// VAO
	glGenVertexArrays(1, &VAO);

	// Bind VAO
	glBindVertexArray(VAO);

	// Copy vertex data into VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// Copy our vertices array into a buffer that openGL can use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Set te vertex attribute pointers, (tell OpenGL how we segment data)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	
	// LETS GOOO Render Loop!
	while(!glfwWindowShouldClose(window)){
		// input
		ProcessInput(window);

		//rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// Set color uniform
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		float redValue = sin(timeValue + 2.0f * M_PI / 3.0f) / 2.0f + 0.5f;
		float blueValue = sin(timeValue + 4.0f * M_PI / 3.0f) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);

		// Draw Triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);







		// check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwTerminate();
	return 0;
}
