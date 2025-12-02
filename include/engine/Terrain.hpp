#ifndef TERRAIN_HPP
# define TERRAIN_HPP

# include <graphic/FlatMesh.hpp>


class	Terrain
{
	public	:
		unsigned int	width;
		unsigned int	height;
		unsigned int	gridSize;

		FlatMesh	mesh;
		Shader		shader;

		Vector3	position;
		Matrix4	model;
	
	public	:
		Terrain(
			unsigned int	width,
			unsigned int	height,
			unsigned int	gridSize
		);
};

#endif /* TERRAIN_HPP ======================================================= */
