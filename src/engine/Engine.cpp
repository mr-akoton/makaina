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
	camera(windowWidth, windowHeight, Vector3(0.0f, 100.0f, 0.0f)),
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

	/* --------------------------- // Terrain setup // -------------------------- */

	Terrain	terrain(terrainSize, terrainSize, 1, Vector3(0.0f, 0.0f, 0.0f));
	terrain.setShader(&terrainShader);
	terrain.setNoiseType(FastNoiseLite::NoiseType_Perlin);
	terrain.setNoiseFrequency(0.003f);
	terrain.setNoiseFractalType(FastNoiseLite::FractalType_FBm);
	terrain.setNoiseFractalParameters(8, 2.0f, 0.4f);
	terrain.initNoiseTexture(terrainHeightMapSize, terrainHeightMapSize);
	terrain.setNoiseTextureUV(terrainHeightMapSize, terrainHeightMapSize);

	/* ---------------------------- // Water setup // --------------------------- */

	Water	water(terrainSize, terrainSize, 1, Vector3(0.0f, 40.0f, 0.0f));
	water.setShader(&waterShader);
	water.setNoiseType(FastNoiseLite::NoiseType_Perlin);
	water.setNoiseFrequency(0.003f);
	water.setNoiseFractalType(FastNoiseLite::FractalType_FBm);
	water.setNoiseFractalParameters(8, 2.0f, 0.4f);
	water.setNoiseTextureUV(waterHeightMapSize, waterHeightMapSize);
	water.initNoiseTexture(waterHeightMapSize, waterHeightMapSize);
	water.initEffects(window);

	/* -------------------------------- MAIN LOOP ------------------------------- */

	FBO	depthFBO;

	depthFBO.bind();

	depthTexture = new FramebufferTexture(window.width, window.height, 3, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT);
	depthTexture->setFilter(GL_NEAREST);
	depthTexture->setWrap(GL_CLAMP_TO_BORDER);
	depthTexture->setWrapBorderColor(Vector4(0.0f));
	depthFBO.attachTexture(*depthTexture, GL_DEPTH_ATTACHMENT);

	depthFBO.checkAttachements();
	depthFBO.unbind();


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
		
		_renderDepth(terrain, water, depthFBO);
		_renderSceneForWater(terrain, water);
		_renderScene(terrain, water);

		_renderUI(terrain, water);
		window.update();
	}

	delete depthTexture;
}

void	Engine::_renderDepth(Terrain& terrain, Water&, FBO& depthFBO)
{
		depthFBO.bind();

		glViewport(0, 0, window.width, window.height);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		
		terrain.noiseTexture->bind();
		terrain.shader->enable();
		terrain.shader->setInt("heightFactor", terrain.heightFactor);
		terrain.shader->setVec3("lightPosition", lightPosition);
		terrain.shader->setVec3("lightColor", lightColor);
		terrain.draw(camera);
		terrain.noiseTexture->unbind();
		
		depthFBO.unbind();
}


void	Engine::_renderSceneForWater(Terrain& terrain, Water& water)
{
		/* ---------------------------- // Reflection // ---------------------------- */
		water.reflectionFBO.bind();

		glViewport(0, 0, window.width, window.height);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		
		Camera	reflectionCamera = camera;
		reflectionCamera.orientation.y = -camera.orientation.y;
		reflectionCamera.position.y = water.position.y - (camera.position.y - water.position.y);
		reflectionCamera.updateMatrix();

		terrain.noiseTexture->bind();
		terrain.draw(reflectionCamera, Vector4(0.0f, 1.0f, 0.0f, -water.position.y + 1));
		terrain.noiseTexture->unbind();
		
		water.reflectionFBO.unbind();

		/* ---------------------------- // Refraction // ---------------------------- */
		water.refractionFBO.bind();

		glViewport(0, 0, window.width, window.height);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		terrain.noiseTexture->bind();
		terrain.draw(camera, Vector4(0.0f, -1.0f, 0.0f, water.position.y));
		terrain.noiseTexture->unbind();
		
		water.refractionFBO.unbind();
}

void	Engine::_renderScene(Terrain& terrain, Water& water)
{
		glViewport(0, 0, window.width, window.height);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		
		// ----- [ Terrain ] ----- //
		terrain.noiseTexture->bind();
		terrain.draw(camera);
		terrain.noiseTexture->unbind();

		// ------ [ Water ] ------ //
		water.noiseTexture->bind();
		water.reflectionTexture->bind();
		water.refractionTexture->bind();
		depthTexture->bind();

		water.shader->enable();
		water.shader->setVec3("color", water.color);
		water.shader->setVec3("lightPosition", lightPosition);
		water.shader->setVec3("lightColor", lightColor);
		water.shader->setVec3("cameraPosition", camera.position);
		water.shader->setFloat("height", water.position.y);
		water.shader->setFloat("globalTime", glfwGetTime());
		water.reflectionTexture->textureUnit(*(water.shader), "reflectionTexture", 1);
		water.refractionTexture->textureUnit(*(water.shader), "refractionTexture", 2);
		depthTexture->textureUnit(*(water.shader), "depthTexture", 3);
		water.draw(camera);
		
		water.noiseTexture->unbind();
		water.reflectionTexture->unbind();
		water.refractionTexture->unbind();
		depthTexture->unbind();
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
	/* Update window title once per second to avoid excessive OS calls */
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

	ImGui::Text("Water");
	ImGui::SliderFloat("Water Level", &water.position.y, 0.0f, 1000.0f, "%.1f");
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
