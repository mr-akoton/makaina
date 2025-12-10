#ifndef TERRAIN_HPP
# define TERRAIN_HPP

#ifndef GLM_ENABLE_EXPERIMENTAL
# define GLM_ENABLE_EXPERIMENTAL
#endif

# include <graphic/FlatMesh.hpp>
# include <core/Shader.hpp>
# include <core/Camera.hpp>

# include <glm/gtx/transform.hpp>
# include <noise/FastNoiseLite.h>


class	Terrain
{
	public	:
		unsigned int	width;
		unsigned int	height;
		unsigned int	gridSize;

		FlatMesh		mesh;
		FastNoiseLite	noise;
		NoiseTexture	*noiseTexture;

		int			heightFactor;
		Vector3		position;
		Matrix4		model;

		Shader		*shader = nullptr;
	
	public	:
		Terrain(
			unsigned int	width,
			unsigned int	height,
			unsigned int	gridSize,
			Vector3			position
		);
		~Terrain();

		void	initNoiseTexture(unsigned int width, unsigned int height);
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

		void	setShader(Shader* shader);

		void	draw(
			Camera&	camera, 
			Vector4	clipPlane = Vector4(0.0f)
		);
};

#endif /* TERRAIN_HPP ======================================================= */
