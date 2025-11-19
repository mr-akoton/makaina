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

		Vector3	color0;
		Vector3	color1;
		Vector3	color2;

		Mesh			mesh;
		FastNoiseLite	noise;

		Vector3	position;
		Matrix4	model;

	public	:
		Terrain(int width, int height, float gridSize, float amplitude);

		void	setPosition(Vector3 position);
		void	generateTerrain(void);
		Vector3	getColorBySlope(Vector3 normal);

		void	render(Shader& shader, Camera& camera);
};

#endif /* TERRAIN_HPP ======================================================= */
