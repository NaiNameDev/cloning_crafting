#include <iostream>
#include <cstdlib>
#include <random>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef IMG_ENABLE
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#endif

#include <voxel_backrooms/shader.hpp>
#include "src/shader.cpp"
#include <voxel_backrooms/world.hpp>
#include "src/world.cpp"

#define WIDTH 1280.0f
#define HEIGHT 720.0f
#define NEAR 0.1f
#define FAR 100.0f
#define FOV 90.0f

int main() {
#ifdef IMG_ENABLE
	stbi_set_flip_vertically_on_load(true);
#endif
	if (!glfwInit()) return -1;
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "voxel_backrooms", NULL, NULL);
	//glfwSetCursorPosCallback(window, cursor_position_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	glm::mat4 proj = glm::perspective(glm::radians(FOV), WIDTH / HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = glm::mat4(1.0f);

	Shader world_shader;
	world_shader.init_shader_program();
	world_shader.attach_shader("VERTEX",   "shaders/world/world_vert.glsl");
	world_shader.attach_shader("GEOMETRY", "shaders/world/world_geom.glsl");
	world_shader.attach_shader("FRAGMENT", "shaders/world/world_frag.glsl");
	world_shader.create_shader_program();

	World test(glm::vec3(0,0,0), 0);
	test.generate_world_mesh(glm::vec3(0,0,0));
	test.prepare_buffers();

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		world_shader.execute();
		world_shader.set_uniform("fin_mat", proj * view);
		world_shader.set_uniform("utime", (float)(glfwGetTime()));
		test.draw();

		glfwSwapBuffers(window);
        glfwPollEvents();
	}

	glfwDestroyWindow(window);
    glfwTerminate();
}
