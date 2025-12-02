#ifndef TERRAIN_HPP
# define TERRAIN_HPP

#ifndef GLM_ENABLE_EXPERIMENTAL
# define GLM_ENABLE_EXPERIMENTAL
#endif

# include <graphic/FlatMesh.hpp>
# include <core/Camera.hpp>

# include <glm/gtx/transform.hpp>


class	Terrain
{
	public	:
		unsigned int	width;
		unsigned int	height;
		unsigned int	gridSize;

		FlatMesh		mesh;

		Vector3			position;
		Matrix4			model;
	
	public	:
		Terrain(
			unsigned int	width,
			unsigned int	height,
			unsigned int	gridSize,
			Vector3			position
		);

		void	draw(Shader& shader, Camera& camera);
};

#endif /* TERRAIN_HPP ======================================================= */
