#include <engine/Terrain.hpp>
#include <iostream>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

Terrain::Terrain(
	int		width,
	int		height,
	int		gridSize,
	Shader&	shader,
	Vector3	position,
	Vector3	color
):
	width(width),
	height(height),
	heightScale(500.0f),
	gridSize(gridSize),
	shader(shader),
	mesh(width, height, gridSize),
	position(position),
	color(color),
	model(1.0f)
{
	model = glm::translate(model, position);
}

Terrain::~Terrain()
{
	delete heightMap;
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

/* ------------------------------ Noise Methods ----------------------------- */

void	Terrain::setNoiseTexture(int textureWidth, int textureHeight)
{
	delete heightMap;

	heightMap = new NoiseTexture(
		noise,
		textureWidth,
		textureHeight,
		NOISE_LAYER,
		GL_RED,
		GL_FLOAT
	);

	for (int y = 0; y < width; y++)
	{
		for (int x = 0; x < height; x++)
		{
			int	i = (y * width) + x;

			mesh.vertices[i].textureUV = Vector2(
				static_cast<float>(x) / (textureWidth - 1),
				static_cast<float>(y) / (textureHeight - 1)
			);
		}
	}

	mesh._assignBuffer();
}

void	Terrain::setNoiseType(FastNoiseLite::NoiseType type)
{
	noise.SetNoiseType(type);
}

void	Terrain::setNoiseFrequency(float frequency)
{
	noise.SetFrequency(frequency);
}

void	Terrain::setNoiseFractalType(FastNoiseLite::FractalType type)
{
	noise.SetFractalType(type);
}

void	Terrain::setNoiseFractalOctaves(int octaves)
{
	noise.SetFractalOctaves(octaves);
}

void	Terrain::setNoiseFractalLacunarity(float lacunarity)
{
	noise.SetFractalLacunarity(lacunarity);
}

void	Terrain::setNoiseFractalGain(float gain)
{
	noise.SetFractalGain(gain);
}

/* ------------------------------ Draw Methods ------------------------------ */

void	Terrain::draw(Camera& camera)
{
	shader.enable();
	shader.setMat4("u_model", model);
	
	if (heightMap != nullptr)
	{
		heightMap->bind();
		heightMap->textureUnit(shader, "u_heightMap", NOISE_LAYER);
	}
	
	mesh.draw(shader, camera);
}
