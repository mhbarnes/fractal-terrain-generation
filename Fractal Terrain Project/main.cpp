#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "window.h"
#include "fractal.h"
#include "bitmap_image.hpp"

int main()
{
	// Shaders input
	std::string temp1 = getFileText("shaders/shader.vert");
	const char* vertexShaderSource = temp1.c_str();
	std::string temp2 = getFileText("shaders/shader.frag");
	const char* fragmentShaderSource = temp2.c_str();

	// Variable declarations
	const char* windowTitle = "Fractal Terrain Project";
	int xResolution = 800;
	int yResolution = 600;
	int xLLCorner = 0;
	int yLLCorner = 0;

	// Initialize GLFW
	glfwInit();

	// Which version of OpenGL to use: this is configured to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Have GLFW explicitly use the core profile (what does that mean?)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window object that will be used for other GLFW operations
	GLFWwindow* window = glfwCreateWindow(xResolution, yResolution, windowTitle, NULL, NULL);

	// Catch if window failed to initialize
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window.\n";

		glfwTerminate();
		return -1;
	}

	// Make context of window the main context (what does context mean?)
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD.\n";

		glfwTerminate();
		return -1;
	}

	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glViewport(xLLCorner, yLLCorner, xResolution, yResolution);

	// Resize callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	int numTriangles = 2 * xResolution * yResolution;
	/*float* vertices = new float[3 * 3 * numTriangles];
	int counter = 0;

	for (int x = 0; x < xResolution; x+=100)
		for (int y = 0; y < yResolution; y+=100)
		{
			vertices[counter++] = 2 * ((float)x / xResolution) - 1;
			vertices[counter++] = 2 * ((float)y / yResolution) - 1;
			vertices[counter++] = 0;
			vertices[counter++] = 2 * ((float)(x + 100) / xResolution) - 1;
			vertices[counter++] = 2 * ((float)y / yResolution) - 1;
			vertices[counter++] = 0;
			vertices[counter++] = 2 * ((float)x / xResolution) - 1;
			vertices[counter++] = 2 * ((float)(y + 100) / yResolution) - 1;
			vertices[counter++] = 0;
			std::cout << 2 * ((float)x / xResolution) - 1 << ", " <<((float)y / yResolution) - 1<< ", "<<0<<std::endl;
			vertices[counter++] = 2 * ((float)((x + 100) / xResolution)) - 1;
			vertices[counter++] = 2 * ((float)(y / yResolution)) - 1;
			vertices[counter++] = 0;
			vertices[counter++] = 2 * ((float)((x + 100) / xResolution)) - 1;
			vertices[counter++] = 2 * ((float)((y + 100) / yResolution)) - 1;
			vertices[counter++] = 0;
			vertices[counter++] = 2 * ((float)(x / xResolution)) - 1;
			vertices[counter++] = 2 * ((float)((y + 100) / yResolution)) - 1;
			vertices[counter++] = 0;
		}
		*/
	float vertices[] =
	{
		 0.0f,  0.0f, 0.0f,
		 0.5f,  0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,

		-0.5f,  0.0f, 0.0f,
		-0.2f,  0.0f, 0.0f,
		 0.0f, -0.3f, 0.0f,
	};
	/*int vertices[] =
	{
		 100, 200, 000,
		 100, 200, 000,
		 100, 500, 000,

		 50, 90, 300,
		 100, 200, 500,
		 100, 500, 300,
	};*/
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	// 1. aPos in vertex shader (location = 0)
	// 2. vec3
	// 3. float
	// 4. data will not be normalized (already normalized)
	// 5. space between consecutive vertex attributes (space between each 3D vertex)
	// 6. 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void*)0);
	// 1. aPos in vertex shader (location = 0)
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	double r = 0;
	double g = 0;
	double b = 0;
	
	// Render Loop (repeat until window closes)
	while (!glfwWindowShouldClose(window))
	{
		// Handle user input
		processInput(window);
		
		
		vertices[0] = r;
		//std::cout << vertices[0] << std::endl;

		glClearColor(.5*(1+sin(r += .0001)), .5*(1 + sin(g += .0006)), .5*(1 + sin(b += .0002)), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		// 1. Type of output
		// 2. Starting index
		// 3. Number of verticies to draw
		glDrawArrays(GL_TRIANGLES, 0, 3 * numTriangles);

		// Swap the color buffer that has been used to draw in during this iteration and show it as output to the screen
		glfwSwapBuffers(window);
		// Checks if any events are triggered, updates the window state, and calls the callback functions
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// End use of GLFW
	glfwTerminate();

	return 0;
}

