#include <core/Window.hpp>
#include <utils/types.hpp>

#include <imgui_impl_glfw.h>

static void frameBufferSizeCallback(GLFWwindow* , int width, int height);

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

Window::Window(void):
	_id(NULL),
	width(0),
	height(0)
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

int	Window::init(unsigned int width, unsigned int height, const char* title)
{
	this->width = width;
	this->height = height;
	
	_id = glfwCreateWindow(width, height, title, NULL, NULL);
	if (_id == NULL)
	{
		return failure;
	}

	glfwMakeContextCurrent(_id);
	glfwSetFramebufferSizeCallback(_id, frameBufferSizeCallback);
	
	return success;
}

void	Window::close(void) const
{
	if (not glfwWindowShouldClose(_id))
	{
		glfwSetWindowShouldClose(_id, true);
	}
}

void	Window::update(void) const
{
	glfwSwapBuffers(_id);
	glfwPollEvents();
}

void	Window::destroy(void)
{
	if (_id != NULL)
	{
		glfwDestroyWindow(_id);
		_id = NULL;
	}
}


/* -------------------------------- Checker --------------------------------- */

bool	Window::shouldClose(void) const
{
	return glfwWindowShouldClose(_id);
}

bool	Window::isKeyPressed(int key) const
{
	return glfwGetKey(_id, key) == GLFW_PRESS;
}

bool	Window::isKeyReleased(int key) const
{
	return glfwGetKey(_id, key) == GLFW_RELEASE;
}

bool	Window::isButtonPressed(int button) const
{
	return glfwGetMouseButton(_id, button) == GLFW_PRESS;
}

bool	Window::isButtonReleased(int button) const
{
	return glfwGetMouseButton(_id, button) == GLFW_RELEASE;
}

/* --------------------------------- Cursor --------------------------------- */

void	Window::setCursorPos(double x, double y) const
{
	glfwSetCursorPos(_id, x, y);
}

void	Window::getCursorPos(double& x, double& y) const
{
	glfwGetCursorPos(_id, &x, &y);
}

void	Window::hideCursor(void) const
{
	glfwSetInputMode(_id, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void	Window::resetCursor(void) const
{
	glfwSetInputMode(_id, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

/* ---------------------------------- ImGui --------------------------------- */

void	Window::initImGui(void) const
{
	ImGui_ImplGlfw_InitForOpenGL(_id, true);

}

/* ========================================================================== */
/*                                  UTILITY                                   */
/* ========================================================================== */

static void frameBufferSizeCallback(GLFWwindow* , int width, int height)
{
	glViewport(0, 0, width, height);
}
