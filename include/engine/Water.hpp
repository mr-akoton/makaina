#ifndef WATER_HPP
# define WATER_HPP

#ifndef GLM_ENABLE_EXPERIMENTAL
# define GLM_ENABLE_EXPERIMENTAL
#endif

# include <core/Object.hpp>
# include <graphic/FlatMesh.hpp>
# include <core/Camera.hpp>

# include <glm/gtx/transform.hpp>
# include <noise/FastNoiseLite.h>


class	Water
{
	public	:
		int 		width;
		int			height;
		int			gridSize;
		
		Shader&		shader;
		
		FlatMesh	mesh;
		Vector3		position;
		Vector3		color;
		Matrix4		model;

	public	:
		Water(
			int		width,
			int		height,
			int		gridSize,
			Shader&	shader,
			Vector3	position = Vector3(0.0f),
			Vector3	color = Vector3(0.0f, 0.0f, 1.0f)
		);
		~Water();

		void	draw(Camera& camera);
};

#endif /* WATER_HPP ========================================================= */
