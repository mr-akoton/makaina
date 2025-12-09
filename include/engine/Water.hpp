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
		unsigned int	width;
		unsigned int	height;
		unsigned int	gridSize;

		FlatMesh		mesh;
		FastNoiseLite	noise;

		Vector3			color;
		Vector3			position;
		Matrix4			model;

	public	:
		Water(
			unsigned int	width,
			unsigned int	height,
			unsigned int	gridSize,
			Vector3			position = Vector3(0.0f),
			Vector3			color = Vector3(0.341f, 0.462f, 1.0f)
		);

		void	setNoiseType(FastNoiseLite::NoiseType type);
		void	setNoiseFrequency(float value);
		void	setNoiseFractalType(FastNoiseLite::FractalType type);
		void	setNoiseFractalParameters(
			int		octaves,
			float	lacunarity,
			float	gain
		);
		void	setNoiseTextureUV(
			unsigned int	noiseWidth,
			unsigned int	noiseHeight
		);

		void	draw(Shader& shader, Camera& camera);
};

#endif /* WATER_HPP ========================================================= */
