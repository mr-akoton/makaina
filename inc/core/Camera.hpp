#ifndef CAMERA_HPP
# define CAMERA_HPP

# include <glm/glm.hpp>

# include <core/Window.hpp>
# include <core/Shader.hpp>
# include <util/types.hpp>

class	Camera
{
	public	:
		int		width;
		int		height;
		float	fov;
		float	near;
		float	far;
		float	ratio;
		
		bool	isMouseFirstClick;
		float	mouseSensitivity;

		float	speed;
		Vector3	up;
		Vector3	position;
		Vector3	orientation;
};

#endif /* CAMERA_HPP ======================================================== */
