#include <iostream>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#define STB_IMAGE_IMPLEMENTATION
//#include <stb/stb_image.h>

#define WIDTH 1280.0f
#define HEIGHT 720.0f
#define NEAR 0.1f
#define FAR 100.0f
#define FOV 90.0f

int main() {
	if (!glfwInit()) return -1;
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//stbi_set_flip_vertically_on_load(true);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "MyWorld", NULL, NULL);
	//glfwSetCursorPosCallback(window, cursor_position_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
        glfwPollEvents();
	}

	glfwDestroyWindow(window);
    glfwTerminate();
}
