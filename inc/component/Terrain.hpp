#ifndef TERRAIN_HPP
# define TERRAIN_HPP

# include <core/Camera.hpp>
# include <core/Shader.hpp>
# include <graphic/Mesh.hpp>
# include <graphic/Texture.hpp>

# include <util/types.hpp>
# include <noise/FastNoiseLite.h>

class	Terrain
{
	public	:
		int				width;
		int				height;
		
		MeshFlat		mesh;
		Vector3			position;
		Matrix4			model;
		Shader			shader;
		
		FastNoiseLite	noise;
		TextureNoise*	noiseTexture;

	public	:
		Terrain(
			int width,
			int height,
			float gridScale = 1.0f,
			Vector3 position = Vector3(0.0f)
		);
		~Terrain();
	
		void	initNoiseTexture(int width, int height);
		void	setNoiseType(FastNoiseLite::NoiseType type);
		void	setNoiseFrequency(float value);
		void	setNoiseFractalType(FastNoiseLite::FractalType type);
		void	setNoiseFractalParameters(
			int octaves,
			float lacunarity,
			float gain
		);
		void	setNoiseTextureUV(int noiseWidth, int noiseHeight);

		void	draw(Camera& camera);
};

#endif /* TERRAIN_HPP ======================================================= */
