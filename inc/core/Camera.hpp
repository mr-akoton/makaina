#ifndef CAMERA_HPP
# define CAMERA_HPP

#ifndef GLM_ENABLE_EXPERIMENTAL
# define GLM_ENABLE_EXPERIMENTAL
#endif

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>
# include <glm/gtx/rotate_vector.hpp>
# include <glm/gtx/vector_angle.hpp>

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
		Matrix4	projection;
	
	public	:
		Camera(const Camera& instance);
		Camera(int width, int height, Vector3 position = Vector3(0.0f));

		Camera&	operator=(const Camera& instance);

		void	handleInput(Window& window);
		void	updateMatrix(void);
		void	updateMatrix(float fovDegree, float near, float far);
		void	updateShaderMatrix(Shader& shader, const char* uniform);

	private	:
		void	_handleKeyInput(Window& window);
		void	_handleMouseInput(Window& window);
};

#endif /* CAMERA_HPP ======================================================== */
