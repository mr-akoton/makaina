#include "imgui.h"
#include <engine/Engine.hpp>
#include <engine/Water.hpp>
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
	terrainHeight(0.0f),
	lightPosition(1.0f, 1.0f, -1.0f),
	lightColor(1.0f),
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

#include <iostream>

void	Engine::run(void)
{
	Shader	terrainShader(
		"shader/terrain-vertex.glsl",
		"shader/terrain-fragment.glsl",
		"shader/terrain-geometry.glsl"
	);
	Shader	waterShader(
		"shader/water-vertex.glsl",
		"shader/water-fragment.glsl",
		"shader/water-geometry.glsl"
	);

	int	terrainSize = 800;
	int	noiseSize = terrainSize + 1;

	Terrain	terrain(terrainSize, terrainSize, 1.0f, Vector2(noiseSize));
	terrain.setNoiseType(FastNoiseLite::NoiseType_Perlin);
	terrain.setNoiseFrequency(0.003f);
	terrain.setNoiseFractalType(FastNoiseLite::FractalType_FBm);
	terrain.setNoiseFractalAttributes(8, 2.0f, 0.4f);

	Water	water(terrainSize / 2.0, terrainSize / 2.0, 2.0f, Vector3(0.0f, 0.0f, 1.0f));

	Texture	heightMap(terrain.noise, noiseSize, noiseSize, 0, GL_RED, GL_FLOAT);

	Camera	camera(window.width, window.height, Vector3(0.0f, 200.0f, 0.0f));

	terrainShader.enable();
	terrainShader.setMat4("model", terrain.model);
	terrainShader.setVec3("lightPosition", lightPosition);
	terrainShader.setVec3("lightColor", lightColor);
	terrainShader.setFloat("cameraNear", 0.1f);
	terrainShader.setFloat("cameraFar", 1000.f);

	waterShader.enable();
	waterShader.setMat4("model", water.model);
	waterShader.setVec3("lightPosition", lightPosition);
	waterShader.setVec3("lightColor", lightColor);
	waterShader.setFloat("cameraNear", 0.1f);
	waterShader.setFloat("cameraFar", 1000.f);

	while (not window.shouldClose())
	{
		_displayFPS();
		_updateDeltaTime();
		_handleInput();
		
		glClearColor(0.85f, 0.85f, 0.90f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		if (not UI.wantCaptureMouse())
		{
			camera.input(window, deltaTime);
		}

		camera.updateMatrix(45.0f, 0.1f, 1000.0f);
		heightMap.bind();
		
		terrainShader.enable();
		terrainShader.setVec3("lightPosition", lightPosition);
		terrainShader.setVec3("lightColor", lightColor);
		terrainShader.setFloat("heightFactor", terrainHeight);
		terrainShader.setVec3("color0", terrain.color0);
		terrainShader.setVec3("color1", terrain.color1);
		terrainShader.setVec3("color2", terrain.color2);
		heightMap.textureUnit(terrainShader, "heightMap", 0);
		
		terrain.render(terrainShader, camera);
		camera.updateShaderMatrix(terrainShader, "cameraMatrix");
		
		waterShader.enable();
		waterShader.setFloat("glTime", glfwGetTime());
		waterShader.setVec3("lightPosition", lightPosition);
		waterShader.setVec3("lightColor", lightColor);
		waterShader.setVec3("color", water.color);
		waterShader.setFloat("level", water.position.y);
		
		camera.updateShaderMatrix(waterShader, "cameraMatrix");
		water.render(waterShader, camera);
		
		
		_renderUI(terrain, water);

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

/* ---------------------------------- Time ---------------------------------- */

void	Engine::_displayFPS(void)
{
	currentTime = glfwGetTime();
	timeDifference = currentTime - previousTime;
	counter++;
	if (timeDifference >= 1.0 / 30.0)
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

void	Engine::_renderUI(Terrain& terrain, Water& water)
{
	UI.createNewFrame();

	ImGui::Begin("Settings");

	ImGui::SliderFloat("Height", &terrainHeight, 0.0f, 1000.0f, "%.1f");
	ImGui::SliderFloat3(
		"Light Position",
		glm::value_ptr(lightPosition),
		-1.0f,
		1.0f,
		"%.2f"
	);

	ImGui::ColorEdit3("Light Color", glm::value_ptr(lightColor));
	ImGui::ColorEdit3("Color 0", glm::value_ptr(terrain.color0));
	ImGui::ColorEdit3("Color 1", glm::value_ptr(terrain.color1));
	ImGui::ColorEdit3("Color 2", glm::value_ptr(terrain.color2));
	
	ImGui::SliderFloat("Water Height", &water.position.y, 0, 1000, "%.1f");
	ImGui::ColorEdit3("Water Color", glm::value_ptr(water.color));

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
