#include <core/Window.hpp>

static void frameBufferSizeCallback(GLFWwindow *window, int width, int height);

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

Window::Window(int width, int height):
	width(width), height(height), id(NULL)
{
	/* Do nothing */
}

Window::~Window(void)
{
	this->destroy();	
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

/* --------------------------------- State ---------------------------------- */

int	Window::init(const char *title)
{
	id = glfwCreateWindow(width, height, title, NULL, NULL);
	if (id == NULL)
	{
		logError("glfwCreateWindow: failed to create window");
		return failure;
	}

	// Should I put them in a separated function (focus()) ?
	glfwMakeContextCurrent(id);
	glfwSetFramebufferSizeCallback(id, frameBufferSizeCallback);
	
	return success;
}

void	Window::close(void)
{
	if (not glfwWindowShouldClose(id))
	{
		glfwSetWindowShouldClose(id, true);
	}
}

void	Window::update(void)
{
	glfwSwapBuffers(id);
	glfwPollEvents();
}

void	Window::destroy(void)
{
	if (id != NULL)
	{
		glfwDestroyWindow(id);
		id = NULL;
	}
}

/* -------------------------------- Checker --------------------------------- */

bool	Window::shouldClose(void) const
{
	return glfwWindowShouldClose(id);
}

bool	Window::isKeyPressed(int key) const
{
	return glfwGetKey(id, key) == GLFW_PRESS;
}

bool	Window::isKeyReleased(int key) const
{
	return glfwGetKey(id, key) == GLFW_RELEASE;
}

bool	Window::isButtonPressed(int button) const
{
	return glfwGetMouseButton(id, button) == GLFW_PRESS;
}

bool	Window::isButtonReleased(int button) const
{
	return glfwGetMouseButton(id, button) == GLFW_RELEASE;
}

/* --------------------------------- Cursor --------------------------------- */

void	Window::setCursorPos(double x, double y)
{
	glfwSetCursorPos(id, x, y);
}

void	Window::getCursorPos(double &x, double &y)
{
	glfwGetCursorPos(id, &x, &y);
}

void	Window::hideCursor(void)
{
	glfwSetInputMode(id, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void	Window::resetCursor(void)
{
	glfwSetInputMode(id, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

/* ========================================================================== */
/*                                  UTILITY                                   */
/* ========================================================================== */

static void frameBufferSizeCallback(GLFWwindow */*window*/, int width,
									int height)
{
	glViewport(0, 0, width, height);
}
