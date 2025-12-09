#ifndef CAMERA_HPP
# define CAMERA_HPP

# include <glad/glad.h>

# include <utils/types.hpp>
# include <core/Window.hpp>
# include <core/Shader.hpp>

class	Camera
{
	public	:
		bool	isMouseFirstClick;
		int		width;
		int		height;
		float	ratio;
		float	speed;
		float	mouseSensitivity;

		Vector3	up;
		Vector3	position;
		Vector3	orientation;
		Matrix4	cameraMatrix;

	public	:
		Camera(const Camera& instance);
		Camera(int width, int height, Vector3 position);

		Camera&	operator=(const Camera& instance);

		void	input(Window& window, float deltaTime);
		void	updateMatrix(float fovDegree, float nearest, float farest);
		void	updateShaderMatrix(Shader& shader, const char* uniform);
	
	private	:
		void	_handleKeyInput(Window& window, float deltaTime);
		void	_handleMouseInput(Window& window, float deltaTime);
};

#endif /* CAMERA_HPP ======================================================== */
