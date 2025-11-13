#include <scene/Terrain.hpp>
#include <glm/gtc/matrix_transform.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

Terrain::Terrain(int width, int height, int gridSize, float amplitude):
	width(width),
	height(height),
	gridSize(gridSize),
	amplitude(amplitude),
	model(glm::mat4(1.0f)),
	position(glm::vec3(0.0f))
{
	model = glm::translate(model, position);
}


/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

/* --------------------------------- Setter --------------------------------- */

void	Terrain::setPosition(glm::vec3 position)
{
	this->position = position;
	model = glm::translate(model, position);
}

/* --------------------------- Terrain Generation --------------------------- */

void	Terrain::generateTerrain(void)
{
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	noise.SetFrequency(0.05f);

	for (int z = 0; z < height; z++)
	{
		for (int x = 0; x < width; x++)
		{
			float	y = noise.GetNoise((float)x, (float)z) * amplitude;

			mesh.vertices.push_back(Vertex{
				glm::vec3(x * gridSize, y, z * gridSize),
				glm::vec3(0.0f),
				glm::vec3(1.0f),
				glm::vec2(0.0f),
			});

			if (z != height - 1 and x != width - 1)
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

	for (size_t i = 0; i < mesh.indices.size(); i += 3)
	{
		GLuint i0 = mesh.indices[i];
		GLuint i1 = mesh.indices[i + 1];
		GLuint i2 = mesh.indices[i + 2];
		
		glm::vec3 v0 = mesh.vertices[i0].position;
		glm::vec3 v1 = mesh.vertices[i1].position;
		glm::vec3 v2 = mesh.vertices[i2].position;
		glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
		
		mesh.vertices[i0].normal += normal;
		mesh.vertices[i1].normal += normal;
		mesh.vertices[i2].normal += normal;
	}
	
	for (auto &v : mesh.vertices) v.normal = glm::normalize(v.normal);

	mesh._assignBuffer();
}

/* ---------------------------------- State --------------------------------- */

void	Terrain::render(Shader &shader, Camera &camera)
{
	mesh.draw(shader, camera);
}
