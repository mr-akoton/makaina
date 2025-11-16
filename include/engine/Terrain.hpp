#ifndef TERRAIN_HPP
# define TERRAIN_HPP

# include <noise/FastNoiseLite.h>

# include <utils/types.hpp>
# include <graphic/Mesh.hpp>


class	Terrain
{
	public	:
		char*	type;
		int		width;
		int		height;
		float	gridSize;
		float	amplitude;

		Mesh			mesh;
		FastNoiseLite	noise;

		Vector3	position;
		Matrix4	model;

	public	:
		Terrain(int width, int height, float gridSize, float amplitude);

		void	setPosition(Vector3 position);
		void	generateTerrain(void);

		void	render(Shader& shader, Camera& camera);
};

#endif /* TERRAIN_HPP ======================================================= */
