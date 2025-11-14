#include <core/Camera.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

Camera::Camera(int width, int height, glm::vec3 position):
	isFirstMouseClick( true ),
	width( width ),
	height( height ),
	ratio( (float)width / height ),
	speed( 5.0f ),
	sensitivity( 2.0f ),
	position( position ),
	orientation( glm::vec3(0.0f, 0.0f, -1.0f) ),
	up( glm::vec3(0.0f, 1.0f, 0.0f) ),
	camMatrix( glm::mat4(1.0f) )
{
	/* Do nothing */
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	Camera::updateMatrix(float fov, float nearest, float farest)
{
	glm::mat4	view = glm::mat4(1.0f);
	glm::mat4	projection = glm::mat4(1.0f);

	view = glm::lookAt(position, position + orientation, up);
	projection = glm::perspective(glm::radians(fov), ratio, nearest, farest);
	camMatrix = projection * view;
}

void	Camera::updateShaderMatrix(Shader &shader, const char *uniform)
{
	shader.setMat4(uniform, camMatrix);
}

#include <iostream>
void	Camera::input(Window &window, float deltaTime)
{
	// Cardinal Movement: UP - DOWN - RIGHT - LEFT
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

	// Fly Movement
	if (window.isKeyPressed(GLFW_KEY_SPACE))
	{
		position += cameraSpeed * up;
	}
	else if (window.isKeyPressed(GLFW_KEY_LEFT_CONTROL))
	{
		position -= cameraSpeed * up;
	}

	
	// Cursor Control
	if (window.isButtonPressed(GLFW_MOUSE_BUTTON_1))
	{
		window.hideCursor();

		if (isFirstMouseClick)
		{
			window.setCursorPos(width / 2.0, height / 2.0);
			isFirstMouseClick = false;
		}

		double		cursorx, cursory;
		float		rotx, roty;
		glm::vec3	newOrientation;

		window.getCursorPos(cursorx, cursory);
		rotx = sensitivity * (float)(cursory - (height / 2.0f)) / height;
		roty = sensitivity * (float)(cursorx - (width / 2.0f)) / width;

		newOrientation = glm::rotate(orientation, glm::radians(-rotx),
			glm::normalize(glm::cross(orientation, up)));

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
		isFirstMouseClick = true;
	}
}
