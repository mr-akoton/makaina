#include <engine/Water.hpp>
#include <glm/gtc/matrix_transform.hpp>

/* ========================================================================== */
/*                                 CONSTRUCTOR                                */
/* ========================================================================== */

Water::Water(int width, int height, float gridSize, Vector3 color):
	width(width),
	height(height),
	gridSize(gridSize),
	color(color),
	position(0.0f, 10.0f, 0.0f),
	model(1.0f)
{
	model = glm::translate(model, position);

	for (int z = 0; z < height; z++)
	{
		for (int x = 0; x < width; x++)
		{
			mesh.vertices.push_back(
				Vertex({
					Vector3(x * gridSize, position.y, z * gridSize),
					Vector3(0.0f),
					color,
					Vector2(0.0f)
				})
			);

			if (x != width - 1 and z != height - 1)
			{
				int	i = (z * width) + x;

				mesh.indices.push_back(i);
				mesh.indices.push_back(i + width);
				mesh.indices.push_back(i + 1);

				mesh.indices.push_back(i + 1);
				mesh.indices.push_back(i + width);
				mesh.indices.push_back(i + width + 1);
			}
		}
	}

	mesh.assignBuffer();
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	Water::setPosition(Vector3 position)
{
	this->position = position;
	model = glm::translate(Matrix4(1.0f), position);
}

void	Water::render(Shader& shader, Camera& camera)
{
	mesh.draw(shader, camera);
}
