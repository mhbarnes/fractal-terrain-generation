#include "window.h"

// Resize Function
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Handle keyboard and mouse input
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

std::string getFileText(const char* path)
{
	std::ifstream input;
	std::string output = "";

	input.open(path);

	if (input.is_open())
	{
		std::string line = "";

		while (std::getline(input, line))
			output += line + '\n';
	}
	else
		std::cout << "Failed to open file at " << path << std::endl;

	return output + '\0';
}