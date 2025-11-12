#include <graphic/Mesh.hpp>
#include <random>
#include <noise/FastNoiseLite.h>

Mesh	getRandomTerrainMesh(int width, int height, int gridSize = 1.0f)
{
	std::vector<Vertex>		vertices;
	std::vector<GLuint>		indices;
	std::vector<Texture>	textures;

 	std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution <> distrib(0, 255); 

	FastNoiseLite	noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	noise.SetFrequency(0.050f);

	// Generate the vertices and indices
	for (int z = 0; z < height; z++)
	{
		for (int x = 0; x < width; x++)
		{
			float	r = static_cast<float>(distrib(gen)) / 255;
			float	g = 0.2f;
			float	b = 0.5f;
			float	h = noise.GetNoise((float)x, (float)z) * 10;

			vertices.push_back( Vertex{ 
					glm::vec3(x * gridSize, h, z * gridSize),
					glm::vec3(0.0f, 1.0f, 0.0f),
					glm::vec3(r, g, b),
					glm::vec2(0.0f, 0.0f)
				}
			);

			int	i = (z * width) + x;
			if (x != width - 1  and z != height - 1)
			{
				indices.push_back(i + width);
				indices.push_back(i);
				indices.push_back(i + 1);

				indices.push_back(i + width);
				indices.push_back(i + 1);
				indices.push_back(i + width + 1);
			}
		}
	}

	return Mesh(vertices, indices, textures);
}