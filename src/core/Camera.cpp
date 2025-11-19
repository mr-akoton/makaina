#include <core/Camera.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

/* ========================================================================== */
/*                                 CONSTRUCTOR                                */
/* ========================================================================== */

Camera::Camera(int width, int height, Vector3 position):
	isMouseFirstClick(true),
	width(width),
	height(height),
	ratio((float)width / height),
	speed(20.0f),
	mouseSensitivity(20.0f),
	up(0.0f, 1.0f, 0.0f),
	position(position),
	orientation(0.0f, 0.0f, 1.0f),
	cameraMatrix(1.0f)
{
	/* Do nothing */
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	Camera::updateMatrix(float fov, float nearest, float farest)
{
	Matrix4	view(1.0f);
	Matrix4	projection(1.0f);

	view = glm::lookAt(position, position + orientation, up);
	projection = glm::perspective(glm::radians(fov), ratio, nearest, farest);
	cameraMatrix = projection * view;
}

void	Camera::updateShaderMatrix(Shader& shader, const char* uniform)
{
	shader.setMat4(uniform, cameraMatrix);
}

void	Camera::input(Window& window, float deltaTime)
{
	_handleKeyInput(window, deltaTime);
	_handleMouseInput(window, deltaTime);
}

void	Camera::_handleKeyInput(Window& window, float deltaTime)
{
	float	cameraSpeed = speed * deltaTime;

	if (window.isKeyPressed(GLFW_KEY_W))
	{
		position +=  cameraSpeed * orientation;
	}
	else if (window.isKeyPressed(GLFW_KEY_S))
	{
		position -= cameraSpeed * orientation;
	}
	if (window.isKeyPressed(GLFW_KEY_D))
	{
		position += cameraSpeed * glm::normalize(glm::cross(orientation, up));
	}
	else if (window.isKeyPressed(GLFW_KEY_A))
	{
		position -= cameraSpeed * glm::normalize(glm::cross(orientation, up));
	}

	if (window.isKeyPressed(GLFW_KEY_SPACE))
	{
		position += cameraSpeed * up;
	}
	else if (window.isKeyPressed(GLFW_KEY_LEFT_CONTROL))
	{
		position -= cameraSpeed * up;
	}
}

void	Camera::_handleMouseInput(Window& window, float)
{
	if (window.isButtonPressed(GLFW_MOUSE_BUTTON_1))
	{
		window.hideCursor();

		if (isMouseFirstClick)
		{
			window.setCursorPos(width / 2.0, height / 2.0);
			isMouseFirstClick = false;
		}

		float	rotx, roty;
		double	cursorx, cursory;
		Vector3	newOrientation;

		window.getCursorPos(cursorx, cursory);
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
		window.setCursorPos(width / 2.0, height / 2.0);
	}
	else if (window.isButtonReleased(GLFW_MOUSE_BUTTON_1))
	{
		window.resetCursor();
		isMouseFirstClick = true;
	}
}
