# include <core/Window.hpp>
# include <util/types.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

Window::Window(void):
	_isInitialized(false),
	_id(nullptr),
	width(0),
	height(0)
{
	/* Do nothing */
}

Window::~Window()
{
	this->destroy();
}

/* ========================================================================== */
/*                                   GETTER                                   */
/* ========================================================================== */

bool	Window::isOpen(void) const
{
	return not glfwWindowShouldClose(_id);
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

void	Window::getCursorPosition(double& x, double& y) const
{
	glfwGetCursorPos(_id, &x, &y);
}

/* ========================================================================== */
/*                                   SETTER                                   */
/* ========================================================================== */

void	Window::setCursorPosition(double x, double y) const
{
	glfwSetCursorPos(_id, x, y);
}

void	Window::hideCursor(void) const
{
	glfwSetInputMode(_id, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void	Window::resetCursor(void) const
{
	glfwSetInputMode(_id, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

/* ========================================================================== */
/*                                    STATE                                   */
/* ========================================================================== */

static void frameBufferSizeCallback(GLFWwindow* , int width, int height)
{
    glViewport(0, 0, width, height);
}

int	Window::init(GLuint width, GLuint height, const char* title)
{
	// Avoid any second call
	if (_isInitialized) return success;

	this->width = width;
	this->height = height;

	_id = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (_id == nullptr) return failure;

    glfwMakeContextCurrent(_id);
    glfwSetFramebufferSizeCallback(_id, frameBufferSizeCallback);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(_id, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	_isInitialized = true;
	return success;
}

void	Window::update(void) const
{
	glfwSwapBuffers(_id);
}

void	Window::pollEvents(void) const
{
	glfwPollEvents();
}

void	Window::clear(Color3 color, GLbitfield mask)
{
	glClearColor(color.r, color.g, color.b, 1.0f);
	glClear(mask);
}

void	Window::close(void) const
{
	if (not glfwWindowShouldClose(_id))
		glfwSetWindowShouldClose(_id, true);
}

void	Window::destroy(void)
{
	if (_id != nullptr)
	{
		glfwDestroyWindow(_id);
		_id = nullptr;
	}
}
