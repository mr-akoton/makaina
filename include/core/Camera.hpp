#ifndef CAMERA_HPP
# define CAMERA_HPP

# include <glad/glad.h>
# include <glm/glm.hpp>

# include <core/Shader.hpp>
# include <core/Window.hpp>


class	Camera
{
	public	:
		bool	isFirstMouseClick;

		int		width;
		int		height;
		float	ratio;
		float	speed;
		float	sensitivity;

		glm::vec3	position;
		glm::vec3	orientation;
		glm::vec3	up;
		glm::mat4	camMatrix;


	public	:
		Camera(int width, int height, glm::vec3 position);
		
		void	input(Window &window, float deltaTime);
		void	updateMatrix(float fov, float nearest, float farest);
		void	updateShaderMatrix(Shader &shader, const char *uniform);
};

#endif // CAMERA_HPP
