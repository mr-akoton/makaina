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

	Shader	framebufferShader(
		"shader/framebuffer-vertex.glsl",
		"shader/framebuffer-fragment.glsl"
	);

	int	terrainSize = 800;
	int	noiseSize = terrainSize + 1;

	Terrain	terrain(terrainSize, terrainSize, 1.0f, Vector2(noiseSize));
	terrain.setNoiseType(FastNoiseLite::NoiseType_Perlin);
	terrain.setNoiseFrequency(0.003f);
	terrain.setNoiseFractalType(FastNoiseLite::FractalType_FBm);
	terrain.setNoiseFractalAttributes(8, 2.0f, 0.4f);

	Texture	heightMap(terrain.noise, noiseSize, noiseSize, 0, GL_RED, GL_FLOAT);

	Camera	camera(window.width, window.height, Vector3(0.0f, 200.0f, 0.0f));

	terrainShader.enable();
	terrainShader.setMat4("model", terrain.model);
	terrainShader.setVec3("lightPosition", lightPosition);
	terrainShader.setVec3("lightColor", lightColor);
	terrainShader.setFloat("cameraNear", 0.1f);
	terrainShader.setFloat("cameraFar", 1000.f);

	float rectangleVertices[] =
	{
		// Coords    // texCoords
		1.0f, -1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		-1.0f,  1.0f,  0.0f, 1.0f,

		1.0f,  1.0f,  1.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f,  0.0f, 1.0f
	};

	GLuint	rectVAO;
	GLuint	rectVBO;
	glGenVertexArrays(1, &rectVAO);
	glGenBuffers(1, &rectVBO);
	glBindVertexArray(rectVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	GLuint FBO;
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	GLuint framebufferTexture;
	glGenTextures(1, &framebufferTexture);
	glBindTexture(GL_TEXTURE_2D, framebufferTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window.width, window.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);

	GLuint RBO;
	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, window.width, window.height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "Framebuffer error: " << fboStatus << std::endl;

	while (not window.shouldClose())
	{
		_displayFPS();
		_updateDeltaTime();
		_handleInput();
		
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glClearColor(0.85f, 0.85f, 0.90f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		if (not UI.wantCaptureMouse())
		{
			camera.input(window, deltaTime);
		}

		heightMap.bind();

		camera.updateMatrix(45.0f, 0.1f, 1000.0f);
		terrain.render(terrainShader, camera);
		
		terrainShader.enable();
		terrainShader.setVec3("lightPosition", lightPosition);
		terrainShader.setVec3("lightColor", lightColor);
		terrainShader.setFloat("heightFactor", terrainHeight);
		terrainShader.setVec3("color0", terrain.color0);
		terrainShader.setVec3("color1", terrain.color1);
		terrainShader.setVec3("color2", terrain.color2);
		heightMap.textureUnit(terrainShader, "heightMap", 0);
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		framebufferShader.enable();
		glBindVertexArray(rectVAO);
		glDisable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, framebufferTexture);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		_renderUI(terrain);

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

void	Engine::_renderUI(Terrain& terrain)
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
