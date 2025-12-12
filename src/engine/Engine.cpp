#include "imgui.h"
#include <engine/Engine.hpp>
#include <engine/Water.hpp>
#include <engine/Terrain.hpp>
#include <graphic/FlatMesh.hpp>
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
	camera(windowWidth, windowHeight, Vector3(0.0f, 250.0f, 0.0f)),
	lightPosition(0.0f, -1.0f, 0.0f),
	lightColor(1.0f),
	deltaTime(0.0f),
	previousTime(0.0),
	currentTime(0.0),
	timeDifference(0.0),
	counter(0)
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
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

	/* ------------------------------ // Shader // ------------------------------ */

	Shader	terrainShader(
		"shader/terrain-vertex.glsl",
		"shader/terrain-fragment.glsl"
	);
	
	Shader	waterShader(
		"shader/water-vertex.glsl",
		"shader/water-fragment.glsl"
	);

	/* ---------------------------------- SCENE --------------------------------- */

	Terrain	terrain(499, 499, 1.0f, terrainShader);
	terrain.setNoiseType(FastNoiseLite::NoiseType_Perlin);
	terrain.setNoiseFrequency(0.003f);
	terrain.setNoiseFractalType(FastNoiseLite::FractalType_FBm);
	terrain.setNoiseFractalOctaves(8);
	terrain.setNoiseFractalLacunarity(2.0f);
	terrain.setNoiseFractalGain(0.4f);
	terrain.setNoiseTexture(1000, 1000);

	Water water(499, 499, 1.0f, waterShader, Vector3(0.0f, 15.0f, 0.0f));

	/* -------------------------------- MAIN LOOP ------------------------------- */


	while (not window.shouldClose())
	{
		window.pollEvents();

		_displayFPS();
		_updateDeltaTime();
		_handleInput();

		if (not UI.wantCaptureMouse())
		{
			camera.input(window, deltaTime);
		}

		camera.updateMatrix();

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		terrainShader.enable();
		terrainShader.setInt("u_heightScale", terrain.heightScale);
		terrainShader.setVec3("u_lightPosition", lightPosition);
		terrainShader.setVec3("u_lightColor", lightColor);
		terrain.draw(camera);

		waterShader.enable();
		waterShader.setVec3("u_lightPosition", lightPosition);
		waterShader.setVec3("u_lightColor", lightColor);
		water.draw(camera);

		_renderUI(terrain, water);

		window.update();
	}
}

void	Engine::_renderDepth(Terrain& , Water&, FBO& )
{

}

void	Engine::_renderScene(Terrain& , Water& )
{
		
}

/* ---------------------------------- Input --------------------------------- */

void	Engine::_handleInput(void)
{
	if (window.isKeyPressed(GLFW_KEY_ESCAPE))
	{
		window.close();
	}
}

/* ---------------------------------- Time ---------------------------------- */

void	Engine::_displayFPS(void)
{
	currentTime = glfwGetTime();
	timeDifference = currentTime - previousTime;
	counter++;
	if (timeDifference >= 1.0)
	{
		std::string	FPS = std::to_string((1.0 / timeDifference) * counter);
		std::string	ms = std::to_string((timeDifference / counter) * 1000);
		std::string newTitle = "Makaina - " + FPS + "FPS | " + ms + "ms";
		window.setWindowTitle(newTitle);
		previousTime = currentTime;
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

void	Engine::_renderUI(Terrain& terrain, Water& )
{
	UI.createNewFrame();

	ImGui::Begin("Setting");

	ImGui::Text("Light");
	ImGui::SliderFloat3("Light Position", glm::value_ptr(lightPosition), -1.0f, 1.0f);

	ImGui::Text("Terrain");
	ImGui::SliderInt("Terrain Height", &terrain.heightScale, 0, 1000);

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
