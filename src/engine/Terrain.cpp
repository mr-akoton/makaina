#include <engine/Terrain.hpp>

/* ========================================================================== */
/*                                 CONSTRUCTOR                                */
/* ========================================================================== */

Terrain::Terrain(
	unsigned int	width,
	unsigned int	height,
	unsigned int	gridSize,
	Vector3			position = Vector3(0.0f)
):
	width(width),
	height(height),
	gridSize(gridSize),
	mesh(width, height, gridSize),
	heightFactor(250.0f),
	position(position),
	model(1.0f)
{
	model = glm::translate(model, position);
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

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

void	Terrain::setNoiseFractalParameters(
	int		octaves,
	float	lacunarity,
	float	gain
)
{
	noise.SetFractalOctaves(octaves);
	noise.SetFractalLacunarity(lacunarity);
	noise.SetFractalGain(gain);
}

void	Terrain::setNoiseTextureUV(
	unsigned int	noiseWidth,
	unsigned int	noiseHeight
)
{
	for (unsigned int z = 0; z < height; z++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			unsigned int	i = (z * width) + x;
			
			mesh.vertices[i].textureUV = Vector2(
				static_cast<float>(x) / (noiseWidth - 1),
				static_cast<float>(z) / (noiseHeight - 1)
			);
		}
	}

	mesh._assignBuffer();
}

void	Terrain::draw(Shader& shader, Camera& camera)
{
	shader.enable();
	shader.setMat4("model", model);
	camera.updateShaderMatrix(shader, "cameraMatrix");

	mesh.draw(shader, camera);
}
