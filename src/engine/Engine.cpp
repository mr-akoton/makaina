#include "imgui.h"
#include <engine/Engine.hpp>
#include <engine/Water.hpp>
#include <engine/Terrain.hpp>
#include <graphic/ScreenMesh.hpp>
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
	cameraFOV(45.0f),
	cameraNearest(0.1f),
	cameraFarthest(1000.0f),
	lightPosition(1.0f, -1.0f, 1.0f),
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
	const unsigned int	terrainSize = 499;
	const unsigned int	terrainHeightMapSize = 1000;
	const unsigned int	waterHeightMapSize = 1000;

	/* ------------------------------ // Shader // ------------------------------ */

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

	Shader	screenShader(
		"shader/screen-vertex.glsl",
		"shader/screen-fragment.glsl"
	);

	/* --------------------------- // Terrain setup // -------------------------- */

	Terrain	terrain(terrainSize, terrainSize, 1, Vector3(0.0f, 0.0f, 0.0f));
	terrain.setNoiseType(FastNoiseLite::NoiseType_Perlin);
	terrain.setNoiseFrequency(0.003f);
	terrain.setNoiseFractalType(FastNoiseLite::FractalType_FBm);
	terrain.setNoiseFractalParameters(8, 2.0f, 0.4f);
	terrain.setNoiseTextureUV(terrainHeightMapSize, terrainHeightMapSize);

	/* ---------------------------- // Water setup // --------------------------- */

	Water	water(terrainSize, terrainSize, 1, Vector3(0.0f, 10.0f, 0.0f));
	water.setNoiseType(FastNoiseLite::NoiseType_Perlin);
	water.setNoiseFrequency(0.003f);
	water.setNoiseFractalType(FastNoiseLite::FractalType_FBm);
	water.setNoiseFractalParameters(8, 2.0f, 0.4f);
	water.setNoiseTextureUV(waterHeightMapSize, waterHeightMapSize);

	FBO	reflectionFBO;
	
	reflectionFBO.bind();

	FramebufferTexture	reflectionTexture(window.width, window.height, 1, GL_RGB, GL_RGB, GL_FLOAT);
	reflectionTexture.setFilter(GL_LINEAR);
	reflectionFBO.attachTexture(reflectionTexture);
	
	RBO	reflectionRBO;
	reflectionRBO.bind();
	reflectionRBO.setStorage(window.width, window.height);
	reflectionRBO.unbind();
	reflectionFBO.attachRenderbuffer(reflectionRBO);

	reflectionFBO.checkAttachements();
	
	reflectionFBO.unbind();

	/* --------------------------- // Camera setup // --------------------------- */

	Camera	camera(window.width, window.height, Vector3(0.0f, 100.0f, 0.0f));

	/* ----------------------------- // Noise Map // ---------------------------- */

	NoiseTexture	terrainHeightMap(terrain.noise, terrainHeightMapSize, terrainHeightMapSize, 0, GL_RED, GL_FLOAT);
	terrainHeightMap.textureUnit(terrainShader, "heightMap", 0);
	terrainShader.setInt("heightFactor", terrain.heightFactor);
	terrainShader.setVec3("lightPosition", lightPosition);
	terrainShader.setVec3("lightColor", lightColor);

	NoiseTexture	waterHeightMap(water.noise, waterHeightMapSize, waterHeightMapSize, 0, GL_RED, GL_FLOAT);
	waterHeightMap.textureUnit(waterShader, "heightMap", 0);
	waterShader.setVec3("lightPosition", lightPosition);
	waterShader.setVec3("lightColor", lightColor);

	/* -------------------------------- MAIN LOOP ------------------------------- */

	while (not window.shouldClose())
	{
		_displayFPS();
		_updateDeltaTime();
		_handleInput();

		if (not UI.wantCaptureMouse())
		{
			camera.input(window, deltaTime);
		}

		reflectionFBO.bind();

		glViewport(0, 0, window.width, window.height);
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		Camera	reflectionCamera = camera;
		reflectionCamera.orientation.y = -camera.orientation.y;
		reflectionCamera.position.y = water.position.y + 11 - camera.position.y;
		reflectionCamera.updateMatrix(cameraFOV, cameraNearest, cameraFarthest);

		// ----- [ Terrain ] ----- //
		terrainHeightMap.bind();
		
		terrainShader.enable();
		terrainShader.setInt("heightFactor", terrain.heightFactor);
		terrainShader.setVec3("lightPosition", lightPosition);
		terrainShader.setVec3("lightColor", lightColor);
		terrain.draw(terrainShader, reflectionCamera);
		
		terrainHeightMap.unbind();
		
		reflectionFBO.unbind();
		
		glViewport(0, 0, window.width, window.height);
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		
		camera.updateMatrix(cameraFOV, cameraNearest, cameraFarthest);
		
		// ----- [ Terrain ] ----- //
		terrainHeightMap.bind();
		terrain.draw(terrainShader, camera);
		terrainHeightMap.unbind();
		
		
		// ------ [ Water ] ------ //
		waterHeightMap.bind();
		reflectionTexture.bind();
		
		waterShader.enable();
		waterShader.setVec3("lightPosition", lightPosition);
		waterShader.setVec3("lightColor", lightColor);
		waterShader.setFloat("globalTime", glfwGetTime());
		reflectionTexture.textureUnit(waterShader, "reflectionTexture", 1);
		water.draw(waterShader, camera);
		
		waterHeightMap.unbind();		
		reflectionTexture.unbind();

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
	(void)water;
	UI.createNewFrame();

	ImGui::Begin("Setting");
	
	ImGui::Text("Terrain");
	ImGui::SliderInt("Height", &terrain.heightFactor, -1000, 1000, "%d");
	
	ImGui::Text("Light");
	ImGui::SliderFloat3("Direction", glm::value_ptr(lightPosition), -1, 1, "%.3f");
	ImGui::ColorEdit3("Color", glm::value_ptr(lightColor));

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
