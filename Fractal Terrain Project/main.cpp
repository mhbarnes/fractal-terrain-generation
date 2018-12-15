#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "window.h"

int main()
{
	// Variable declarations
	const char* windowTitle = "Fractal Terrain Project";
	int xResolution = 800;
	int yResolution = 600;
	int xLLCorner = 0;
	int yLLCorner = 0;

	// Initialize GLFW
	glfwInit();

	// Which version of OpenGL to use: this is configured to 3.2
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
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

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD.\n";

		glfwTerminate();
		return -1;
	}

	glViewport(xLLCorner, yLLCorner, xResolution, yResolution);

	// Resize callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	float r = 0;
	float g = 0;
	float b = 0;

	// Render Loop (repeat until window closes)
	while (!glfwWindowShouldClose(window))
	{
		// Handle user input
		processInput(window);


		glClearColor(sin(r += .0001), fmod(g += .00015, 1), fmod(b += .0002, 1), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Swap the color buffer that has been used to draw in during this iteration and show it as output to the screen
		glfwSwapBuffers(window);
		// Checks if any events are triggered, updates the window state, and calls the callback functions
		glfwPollEvents();
	}


	// End use of GLFW
	glfwTerminate();

	return 0;
}