#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <util.hpp>
#include <core/Window.hpp>
#include <core/Camera.hpp>
#include <core/Shader.hpp>
#include <graphic/Mesh.hpp>
#include <world/World.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;


/* ========================================================================== */
/*                              OBJECT PROPRETY                               */
/* ========================================================================== */

Vertex	vertices[] = {
	Vertex{ glm::vec3(-1.0f,  1.0f,  0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f) },
	Vertex{ glm::vec3(-1.0f, -1.0f,  0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
	Vertex{ glm::vec3( 1.0f, -1.0f,  0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
	Vertex{ glm::vec3( 1.0f,  1.0f,  0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f) },
};

GLuint	indices[] = {
	0, 1, 2,	0, 2, 3,
};

/* ========================================================================== */
/*                                 MAIN LOOP                                  */
/* ========================================================================== */

int	main(void)
{

	// GLFW: Initialisation and Configuration
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// Create Window
	Window	window(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (window.init("Makaina") == failure)
	{
		glfwTerminate();
		return 1;
	}

	// GLAD: load all OpenGL function pointers
	if (not gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		return 1;
	}
	
	Shader	defaultShader("shader/default-vertex.glsl", "shader/default-fragment.glsl");
	Mesh	terrain = getRandomTerrainMesh(100, 100, 1.0f);

	glm::vec3	terrainPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4	terrainModel = glm::mat4(1.0f);
	terrainModel = glm::translate(terrainModel, terrainPosition);

	defaultShader.enable();
	defaultShader.setMat4("model", terrainModel);

	glEnable(GL_DEPTH_TEST);

	Camera	camera(window.width, window.height, glm::vec3(0.0f, 0.0f, 2.0f));


	// Delta time initialisation
	float	deltaTime = 0.0f;
	float	lastFrame = 0.0f;

	// GLFW: Main loop
	while (not window.shouldClose())
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
		{
			window.close(); // Should it break or continue ?
		}

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		camera.input(window, deltaTime);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);
		terrain.draw(defaultShader, camera);

		window.update();
	}

	defaultShader.destroy();
	window.destroy();
	glfwTerminate();

	return 0;
}
