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
		int 		width;
		int			height;
		int			heightScale;
		int			gridSize;
		
		Shader&		shader;
		
		FlatMesh	mesh;
		Vector3		position;
		Vector3		color;
		Matrix4		model;
		
		FastNoiseLite	noise;
		NoiseTexture*	heightMap = nullptr;

	public	:
		Terrain(
			int		width,
			int		height,
			int		gridSize,
			Shader&	shader,
			Vector3	position = Vector3(0.0f),
			Vector3	color = Vector3(1.0f)
		);
		~Terrain();

		void	setNoiseTexture(int textureWidth, int textureHeight);
		void	setNoiseType(FastNoiseLite::NoiseType type);
		void	setNoiseFrequency(float frequency);
		void	setNoiseFractalType(FastNoiseLite::FractalType type);
		void	setNoiseFractalOctaves(int octaves);
		void	setNoiseFractalLacunarity(float lacunarity);
		void	setNoiseFractalGain(float gain);
		void	draw(Camera& camera);
};

#endif /* TERRAIN_HPP ======================================================= */
