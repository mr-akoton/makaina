#include <core/Engine.hpp>
#include <iostream>

const int	WINDOW_WIDTH = 1280;
const int	WINDOW_HEIGHT = 720;
const char	*WINDOW_TITLE = "Makaina";

int	main(void)
{
	try
	{
		Engine	engine(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
		engine.run();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	// // Terrain Map
	// Shader	defaultShader("shader/default-vertex.glsl", "shader/default-fragment.glsl");
	// Mesh	terrain = getRandomTerrainMesh(50, 50, 10.0f, 1.0f);

	// glm::vec3	terrainPos = glm::vec3(-25.0f, 0.0f, -25.0f);
	// glm::mat4	terrainModel = glm::mat4(1.0f);
	// terrainModel = glm::translate(terrainModel, terrainPos);

	// // Light
	// glm::vec3	lightPos = glm::vec3(50.0f, 50.0f, 0.0f);
	// glm::vec3	lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

	// defaultShader.enable();
	// defaultShader.setMat4("model", terrainModel);
	// defaultShader.setVec3("lightPos", lightPos);
	// defaultShader.setVec3("lightColor", lightColor);

	// Camera	camera(window.width, window.height, glm::vec3(0.0f, 0.0f, 25.0f));


	// // GLFW: Main loop
	// while (not window.shouldClose())
	// {

	// 	camera.updateMatrix(45.0f, 0.1f, 100.0f);
	// 	terrain.draw(defaultShader, camera);



	// 	defaultShader.enable();
	// 	defaultShader.setVec3("lightPos", lightPos);
	// 	defaultShader.setVec3("lightColor", lightColor);

	// 	gui.render();

	// 	window.update();
	// }

	return 0;
}
