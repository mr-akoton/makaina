#include <core/Engine.hpp>
#include <glm/gtc/type_ptr.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

Engine::Engine(int winWidth, int winHeight, const char *windowTitle):
	windowWidth(winWidth),
	windowHeight(winHeight),
	deltaTime(0.0f),
	lastFrame(0.0f)
{
	_initGlfw();
	if (window.init(windowWidth, windowHeight, windowTitle) == -1)
	{
		glfwTerminate();
		throw Engine::WindowInitFailedException();
	}
	_initGlad();
	gui.init(window);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

Engine::~Engine()
{
	gui.shutdown();
	window.destroy();
	glfwTerminate();
}


/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

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

glm::vec3	lightPos = glm::vec3(50.0f, 50.0f, 0.0f);
glm::vec3	lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

void	Engine::run(void)
{
	Shader	defaultShader("shader/default-vertex.glsl",
						  "shader/default-fragment.glsl");

	Terrain		terrain(50, 50, 1.0f, 10.0f);
	terrain.generateTerrain();
	
	defaultShader.enable();
	defaultShader.setMat4("model", terrain.model);
	defaultShader.setVec3("lightPos", lightPos);
	defaultShader.setVec3("lightColor", lightColor);
	
	Camera	camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 25.0f));
	
	while (not window.shouldClose())
	{
		_updateDeltaTime();
		_handleInput();

		glClearColor(0.4f, 0.9f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (not gui.wantCaptureMouse())
		{
			camera.input(window, deltaTime);
		}

		camera.updateMatrix(45.0f, 0.1f, 100.0f);
		terrain.render(defaultShader, camera);
		defaultShader.enable();
		defaultShader.setVec3("lightPos", lightPos);
		defaultShader.setVec3("lightColor", lightColor);

		gui.createNewFrame();
		_renderGUI();

		gui.render();
		window.update();
	}
}


void	Engine::_renderGUI(void)
{
	ImGui::Begin("Settings");
	ImGui::SliderFloat3("Light Position", glm::value_ptr(lightPos), -1000.0f, 1000.0f, "%.1f");
	ImGui::ColorPicker3("Light Color", glm::value_ptr(lightColor));
	ImGui::End();
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
	float	currentFrame = glfwGetTime();

	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}


/* ========================================================================== */
/*                                  EXCEPTION                                 */
/* ========================================================================== */

const char	*Engine::WindowInitFailedException::what(void) const throw()
{
	return "Exception: failed while initiating the window";
}

const char	*Engine::GladLoadFailedException::what(void) const throw()
{
	return "Exception: failed while loading GLAD";
}
