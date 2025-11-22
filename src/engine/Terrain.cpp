#include <engine/Terrain.hpp>
#include <utils/utils.hpp>

#include <glm/gtc/matrix_transform.hpp>

/* ========================================================================== */
/*                                 CONSTRUCTOR                                */
/* ========================================================================== */

Terrain::Terrain(
	int		width,
	int		height,
	float	gridSize,
	Vector2	noiseTextureSize
):
	width(width),
	height(height),
	gridSize(gridSize),
	noiseTextureSize(noiseTextureSize),
	position(Vector3(0.0f)),
	model(Matrix4(1.0f))
{
	model = glm::translate(model, position);
	generateMesh();
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

/* --------------------------------- Setter --------------------------------- */

void	Terrain::setPosition(Vector3 position)
{
	this->position = position;
	model = glm::translate(model, position);
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

void	Terrain::setNoiseFractalAttributes(int octaves, float lacunarity, float gain)
{
	noise.SetFractalOctaves(octaves);
	noise.SetFractalLacunarity(lacunarity);
	noise.SetFractalGain(gain);
}

/* --------------------------- Terrain Generation --------------------------- */

void	Terrain::generateMesh(void)
{
	for (int z = 0; z < height; z++)
	{
		for (int x = 0; x < width; x++)
		{
			mesh.vertices.push_back(
				Vertex({
					Vector3(x * gridSize, 0.0f, z * gridSize),
					Vector3(0.0f),
					Vector3(1.0f),
					Vector2(
						static_cast<float>(z) / (noiseTextureSize.x - 1),
						static_cast<float>(x) / (noiseTextureSize.y - 1)
					)
				})
			);

			if (x != width - 1 and z != height - 1)
			{
				int	i = (z * width) + x;

				mesh.indices.push_back(i + width);
				mesh.indices.push_back(i + 1);
				mesh.indices.push_back(i);

				mesh.indices.push_back(i + width);
				mesh.indices.push_back(i + width + 1);
				mesh.indices.push_back(i + 1);
			}
		}
	}

	mesh.assignBuffer();
}

/* ---------------------------------- State --------------------------------- */

void	Terrain::render(Shader& shader, Camera& camera)
{
	mesh.draw(shader, camera);
}
