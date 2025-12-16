#include <core/Camera.hpp>

/* ========================================================================== */
/*                                 CONSTRUCTOR                                */
/* ========================================================================== */

Camera::Camera(int width, int height, Vector3 position):
	width(width),
	height(height),
	fov(45.0f),
	near(0.1f),
	far(1000.0f),
	ratio((float)width / height),
	isMouseFirstClick(true),
	mouseSensitivity(30.0f),
	speed(100.0f),
	up(0.0f, 1.0f, 0.0f),
	position(position),
	orientation(0.0f, 0.0f, 1.0f),
	projection(1.0f)
{
	/* Do nothing */
}

Camera::Camera(const Camera& instance)
{
	*this = instance;
}

/* ========================================================================== */
/*                                  OPERATOR                                  */
/* ========================================================================== */

Camera&	Camera::operator=(const Camera& instance)
{
	if (this != &instance)
	{
		width = instance.width;
		height = instance.height;
		fov = instance.fov;
		near = instance.near;
		far = instance.far;
		ratio = instance.ratio;
		isMouseFirstClick = instance.isMouseFirstClick;
		mouseSensitivity = instance.mouseSensitivity;
		speed = instance.speed;
		up = instance.up;
		position = instance.position;
		orientation = instance.orientation;
		projection = instance.projection;
	}

	return *this;
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	Camera::updateMatrix(void)
{
	Matrix4	view(1.0f);
	Matrix4	newProjection(1.0f);

	view = glm::lookAt(position, position + orientation, up);
	newProjection = glm::perspective(glm::radians(fov), ratio, near, far);
	projection = newProjection * view;
}

void	Camera::updateMatrix(float fovDegree, float nearest, float farthest)
{
	this->fov = glm::radians(fovDegree);
	this->near = nearest;
	this->far = farthest;

	Matrix4	view(1.0f);
	Matrix4	newProjection(1.0f);

	view = glm::lookAt(position, position + orientation, up);
	newProjection = glm::perspective(fov, ratio, near, farthest);
	projection = newProjection * view;
}

void	Camera::updateShaderMatrix(Shader& shader, const char* uniform)
{
	shader.setMat4(uniform, projection);
}

void	Camera::handleInput(Window& window)

{
	_handleKeyInput(window);
	_handleMouseInput(window);
}

void	Camera::_handleKeyInput(Window& window)
{
	if (window.isKeyPressed(GLFW_KEY_W))
	{
		position +=  speed * orientation;
	}
	else if (window.isKeyPressed(GLFW_KEY_S))
	{
		position -= speed * orientation;
	}

	if (window.isKeyPressed(GLFW_KEY_D))
	{
		position += speed * glm::normalize(glm::cross(orientation, up));
	}
	else if (window.isKeyPressed(GLFW_KEY_A))
	{
		position -= speed * glm::normalize(glm::cross(orientation, up));
	}

	if (window.isKeyPressed(GLFW_KEY_SPACE))
	{
		position += speed * up;
	}
	else if (window.isKeyPressed(GLFW_KEY_LEFT_CONTROL))
	{
		position -= speed * up;
	}
}

void	Camera::_handleMouseInput(Window& window)
{
	if (window.isButtonPressed(GLFW_MOUSE_BUTTON_1))
	{
		window.hideCursor();

		if (isMouseFirstClick)
		{
			window.setCursorPosition(width / 2.0, height / 2.0);
			isMouseFirstClick = false;
		}

		float	rotx, roty;
		double	cursorx(0), cursory(0);
		Vector3	newOrientation;

		window.setCursorPosition(cursorx, cursory);
		rotx = mouseSensitivity * (float)(cursory - (height / 2.0f)) / height;
		roty = mouseSensitivity * (float)(cursorx - (width / 2.0f)) / width;

		newOrientation = glm::rotate(
			orientation,
			glm::radians(-rotx),
			glm::normalize(glm::cross(orientation, up))
		);

		if (glm::abs(glm::angle(newOrientation, up) - glm::radians(90.0f))
			<= glm::radians(85.0f))
		{
			orientation = newOrientation;
		}

		orientation = glm::rotate(orientation, glm::radians(-roty), up);
		window.setCursorPosition(width / 2.0, height / 2.0);
	}
	else if (window.isButtonReleased(GLFW_MOUSE_BUTTON_1))
	{
		window.resetCursor();
		isMouseFirstClick = true;
	}
}
