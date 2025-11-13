#include <core/Window.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

static void frameBufferSizeCallback(GLFWwindow *window, int width, int height);

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

Window::Window(void):
	width(0), height(0), id(NULL)
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

int	Window::init(int width, int height, const char *title)
{
	this->width = width;
	this->height = height;
	
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
