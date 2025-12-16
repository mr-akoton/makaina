#include <component/Terrain.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

Terrain::Terrain(
	int width,
	int height,
	float gridScale,
	Vector3 position
):
	width(width),
	height(height),
	mesh(width, height, gridScale),
	position(position),
	model(1.0f),
	shader("shader/terrain-vertex.glsl", "shader/terrain-fragment.glsl")
{
	model = glm::translate(model, position);
}

Terrain::~Terrain()
{
	/* Do nothing */	
}

/* ========================================================================== */
/*                               NOISE FUNCTION                               */
/* ========================================================================== */


void	Terrain::initNoiseTexture(int width, int height)
{
	noiseTexture = new TextureNoise(noise, width, height, 0, GL_RED, GL_FLOAT);
	noiseTexture->textureUnit(shader, "u_heightMap", 0);
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

void	Terrain::setNoiseFractalParameters(
	int octaves,
	float lacunarity,
	float gain
)
{
	noise.SetFractalOctaves(octaves);
	noise.SetFractalLacunarity(lacunarity);
	noise.SetFractalGain(gain);
}

void	Terrain::setNoiseTextureUV(int noiseWidth, int noiseHeight)
{
	for (int z = 0; z < height; z++)
	{
		for (int x = 0; x < width; x++)
		{
			int	i = (z * width) + x;
			
			mesh.setNoiseUV(
				i,
				Vector2(
					static_cast<float>(x) / (noiseWidth - 1),
					static_cast<float>(z) / (noiseHeight - 1)
				)
			);
		}
	}

	mesh.assignBuffer();
}

/* ========================================================================== */
/*                                    DRAW                                    */
/* ========================================================================== */

void	Terrain::draw(Camera& camera)
{
	mesh.draw(shader, camera);
}