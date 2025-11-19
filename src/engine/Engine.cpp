#include "imgui.h"
#include <engine/Engine.hpp>
#include <engine/Terrain.hpp>
#include <core/Shader.hpp>

#include <glm/gtc/type_ptr.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

Engine::Engine(
	unsigned int	windowWidth,
	unsigned int	windowHeight,
	const char*		windowTitle
):
	deltaTime(0.0f),
	lightPosition(1.0f, 1.0f, -1.0f),
	lightColor(1.0f)
{
	_initGlfw();
	if (window.init(windowWidth, windowHeight, windowTitle) == -1)
	{
		glfwTerminate();
		throw Engine::WindowInitFailedException();
	}
	UI.init(window);
	_initGlad();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

Engine::~Engine()
{
	UI.shutdown();
	window.destroy();
	glfwTerminate();
}

/* ----------------------------- Initialisation ----------------------------- */

void	Engine::_initGlfw(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}

void	Engine::_initGlad(void)
{
	if (not gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		throw Engine::GladLoadFailedException();
	}
}

/* ---------------------------------- Loop ---------------------------------- */

void	Engine::run(void)
{
	Shader	terrainShader(
		"shader/terrain-vertex.glsl",
		"shader/terrain-fragment.glsl"
	);

	int	terrainSize = 800;

	Terrain	terrain(terrainSize, terrainSize, 1.0f, 500.0f);
	terrain.generateTerrain();
	
	Texture	heightMap(terrain.noise, terrainSize, terrainSize, 0, GL_RED, GL_FLOAT);

	terrainShader.enable();
	terrainShader.setMat4("model", terrain.model);
	terrainShader.setVec3("lightPosition", lightPosition);
	terrainShader.setVec3("lightColor", lightColor);

	Camera	camera(
		window.width,
		window.height,
		Vector3(0.0f, 200.0f, 0.0f)
	);

	while (not window.shouldClose())
	{
		_updateDeltaTime();
		_handleInput();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (not UI.wantCaptureMouse())
		{
			camera.input(window, deltaTime);
		}

		camera.updateMatrix(45.0f, 0.1f, 5000.0f);
		terrain.render(terrainShader, camera);
		
		terrainShader.enable();
		terrainShader.setVec3("lightPosition", lightPosition);
		terrainShader.setVec3("lightColor", lightColor);
		heightMap.textureUnit(terrainShader, "heightMap", 0);
		
		heightMap.bind();

		UI.createNewFrame();
		_renderUI();

		window.update();
	}
}


void	Engine::_handleInput(void)
{
	if (window.isKeyPressed(GLFW_KEY_ESCAPE))
	{
		window.close();
	}
}

void	Engine::_updateDeltaTime(void)
{
	static float	lastFrame = 0.0f;
	float			currentFrame = glfwGetTime();

	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

/* -------------------------------- Interface ------------------------------- */

void	Engine::_renderUI(void)
{
	ImGui::Begin("Settings");
	ImGui::SliderFloat3(
		"Light Position",
		glm::value_ptr(lightPosition),
		-1.0f,
		1.0f,
		"%.2f"
	);
	ImGui::ColorPicker3("Light Color", glm::value_ptr(lightColor));
	ImGui::End();

	UI.render();
}

/* ========================================================================== */
/*                                  EXCEPTION                                 */
/* ========================================================================== */

const char	*Engine::WindowInitFailedException::what(void) const noexcept
{
	return "Exception: failed while initiating the window";
}

const char	*Engine::GladLoadFailedException::what(void) const noexcept
{
	return "Exception: failed while loading GLAD";
}
