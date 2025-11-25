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

		Mesh			mesh;
		FastNoiseLite	noise;

		Vector2	noiseTextureSize;
		Vector3	position;
		Matrix4	model;

		Vector3	color0; 
		Vector3	color1;
		Vector3	color2;

	public	:
		Terrain(
			int		width,
			int		height,
			float	gridSize,
			Vector2 noiseTextureSize
		);

		void	setPosition(Vector3 position);
		void	generateMesh(void);

		void	setNoiseType(FastNoiseLite::NoiseType type);
		void	setNoiseFrequency(float frequency);
		void	setNoiseFractalType(FastNoiseLite::FractalType type);
		void	setNoiseFractalAttributes(int octaves, float lacunarity, float gain);

		void	render(Shader& shader, Camera& camera);
};

#endif /* TERRAIN_HPP ======================================================= */
