#include <core/Engine.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

Engine::Engine(void)
{
	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// Initialize Window
	if (_window.init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE.data()) == failure)
	{
		glfwTerminate();
		throw WindowInitFailedException();
	}

	// Initialize GLAD
	if (not gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
		_window.destroy();
        glfwTerminate();
        throw Engine::GladLoadFailedException();
    }
}

Engine::~Engine()
{
	_window.destroy();
}

/* ========================================================================== */
/*                                     RUN                                    */
/* ========================================================================== */

void	Engine::run(void)
{
	Color3	bgColor(0.655f, 0.824f, 0.910f);

	while (_window.isOpen())
	{
		_window.pollEvents();
		_input();
		_window.clear(bgColor, GL_COLOR_BUFFER_BIT);
		_window.update();
	}
}

/* ---------------------------------- Input --------------------------------- */

void	Engine::_input(void) const
{
	if (_window.isKeyPressed(GLFW_KEY_ESCAPE))
		_window.close();
}

/* ========================================================================== */
/*                                  EXCEPTION                                 */
/* ========================================================================== */

const char*	Engine::WindowInitFailedException::what(void) const noexcept
{
	return "Exception: failed while initiating the window";
}

const char*	Engine::GladLoadFailedException::what(void) const noexcept
{
	return "Exception: failed while loading GLAD";
}